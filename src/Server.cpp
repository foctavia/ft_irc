/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:26:02 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/15 12:49:59 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server()
{
	
}

Server::Server( char *port, char *password )
	: _port(port), _password(password), _socketInfo(NULL), _socketFd(-1)
{
	std::cout << "[SERVER]: welcome on port " << port << "!" << std::endl;
	_cmd = new Command;
}

Server::~Server( void )
{
	clean();
}

void	Server::clean( void )
{
	if (_socketInfo)
		freeaddrinfo(_socketInfo);

	for (size_t	i = 0; i < _pollFds.size();)
	{
		close(_pollFds[i].fd);
		i++;
	}
	_pollFds.clear();

	for (size_t	i = 0; i < _users.size();)
	{
		delete _users[i];
		i++;
	}
	_users.clear();
	delete _cmd;
}

int	Server::getListenerSocket( void )
{
	int				listenerFd = -1;
	int				yes = 1;
	int 			status = 0;
	struct addrinfo hints, *tmp;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	status = getaddrinfo(NULL, _port, &hints, &_socketInfo);
	if (status != 0)
		throw std::runtime_error("getaddrinfo()");
	
	// loop through all the results and bind to the first we can
	for (tmp = _socketInfo; tmp != NULL; tmp = tmp->ai_next)
	{
		listenerFd = socket(_socketInfo->ai_family, _socketInfo->ai_socktype, _socketInfo->ai_protocol);
		if (listenerFd < 0)
			continue ;
			
		if (setsockopt(listenerFd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
			throw std::runtime_error("setsockopt()");

		if (bind(listenerFd, _socketInfo->ai_addr, _socketInfo->ai_addrlen) < 0)
		{
			close(listenerFd);
			listenerFd = -1;
			continue ;
		}
		
		break ;
	}
	
	freeaddrinfo(_socketInfo);
	_socketInfo = NULL;

	if (tmp == NULL)
		throw std::runtime_error("failed to bind the socket");

	if (listen(listenerFd, BACKLOG) == -1)
		throw std::runtime_error("failed to listen to the socket");

	return listenerFd;
}

void	Server::addSocket( int newFd )
{
	if (newFd == -1)
		return ;

	struct pollfd	tmp;
	
	tmp.fd = newFd;
	tmp.events = POLLIN;
	
	_pollFds.push_back(tmp);
}

void *getIpAddress(struct sockaddr *socketAddress)
{
    if (socketAddress->sa_family == AF_INET)
        return &(((struct sockaddr_in*)socketAddress)->sin_addr);

    return &(((struct sockaddr_in6*)socketAddress)->sin6_addr);
}

void	Server::run( void )
{
	try
	{
		_socketFd = getListenerSocket();
	}
	catch(const std::exception &e)
	{
		std::cerr << "ERROR: " << e.what() << std::endl;
		return ;
	}

	addSocket(_socketFd);

	while (1)
	{
		if (poll(&_pollFds[0], _pollFds.size(), TIMEOUT) == -1)
			throw std::runtime_error("poll()");
			
		for (size_t i = 0; i < _pollFds.size(); i++)
		{
			if (_pollFds[i].revents & POLLIN)
			{
				if (_pollFds[i].fd == _socketFd)
					newConnection();
				else
					receiveMessage(_pollFds[i]);
			}
		}
	}
}

void	Server::newConnection( void )
{
	struct sockaddr_storage clientAddress;
	socklen_t				addressLength;
	const char				*client;
	int 					newFd;
	char 					remoteIP[INET6_ADDRSTRLEN];


	addressLength = sizeof clientAddress;
	newFd = accept(_socketFd, (struct sockaddr *)&clientAddress, &addressLength);
	if (newFd == -1)
		throw std::runtime_error("accept()");

	addSocket(newFd);

	client = inet_ntop(clientAddress.ss_family, getIpAddress((struct sockaddr*)&clientAddress), remoteIP, INET6_ADDRSTRLEN);

	User	*newUser = new User(_pollFds.back(), client, this);
	
	_users.insert(std::make_pair<int, User*>(newFd, newUser));	
}

void	Server::receiveMessage( struct pollfd pfd )
{
	User *user = (*_users.find(pfd.fd)).second;
	
	char buffer[512];
	memset(buffer, 0, sizeof buffer);

	int nbytes = recv(user->getFd(), buffer, sizeof buffer, 0);

	if (nbytes == 0)
		disconnect(user);
	else if (nbytes < 0)
		throw std::runtime_error("recv()");
	else
	{
		std::string copy(buffer);
		if (copy.find("\r\n") == std::string::npos)
		{
			copy.erase(copy.end() - 1);
			copy.append("\r\n");
		}
		size_t pos;
		while ((pos = copy.find("\r\n")) != std::string::npos)
		{
			std::string cmd = copy.substr(0, pos);
			std::cout << "[SERVER]: receive " << cmd << " from " << user->getFd() << std::endl;
			copy.erase(0, pos + 2);
			// user->input.clear();
			// user->input.append(cmd);
			user->parseMessage(cmd);
			user->getCommand()->execute(user);
			// _cmd->execute(user);
			// sendMessage(user);
		}
		
	}
}

// void	Server::sendMessage( int senderFd, std::string &message )
// {
	
//  	for (size_t j = 0; j < _pollFds.size(); j++)
// 	{
// 		int dest_fd = _pollFds[j].fd;

// 		if (dest_fd != _socketFd && dest_fd != senderFd)
// 		{
// 			std::string msg = message.substr(0, message.size() - 1);
// 			std::cout << "[SERVER]: send " << msg << " to " << dest_fd << "\r\n"; 
// 			if (send(dest_fd, message.c_str(), message.size(), MSG_NOSIGNAL) == -1)
// 				perror("send");
// 		} 
// 	}	
// 	message.clear();
// }



void	Server::disconnect( User* user)
{
	std::cout << "pollserver: socket hung up" << std::endl;

	close(user->getFd());
	// pfd.fd = -1;
	_users.erase(user->getFd());
	delete user;
}

char	*Server::getPort( void ) const
{
	return _port;
}

char	*Server::getPassword( void ) const
{
	return _password;
}
