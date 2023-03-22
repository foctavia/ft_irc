/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:26:02 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/22 14:38:17 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(char *port, char *password)
	: _port(port), _password(password), _socketInfo(NULL), _socketFd(-1)
{
	displayTime();
	std::cout << "[SERVER] " << BOLD << ITALIC << "welcome on port " << port << "!" << RESET << std::endl;
	_cmd = new Command;
	gettimeofday(&_start, NULL);
	std::time_t	now = std::time(0);
	_startingTime = ctime(&now);
}

Server::~Server(void)
{
	
	clean();
}

void	Server::clean(void)
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
	for (size_t	i = 0; i < channels.size();)
	{
		delete channels[i];
		i++;
	}
	channels.clear();
	delete _cmd;
}

int	Server::getListenerSocket(void)
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

void	Server::addSocket(int newFd)
{
	if (newFd == -1)
		return ;

	struct pollfd	tmp;
	
	tmp.fd = newFd;
	tmp.events = POLLIN;
	
	_pollFds.push_back(tmp);
}

void	Server::checkConnection(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	
						
	std::map<int, User *>::iterator it = _users.begin();
	for (; it != _users.end(); ++it)
	{
		User *user = it->second;
		if (user->getStatus()  == STATUS_VALID)
		{
			long	lastPing = (current.tv_sec - _start.tv_sec);
			
			if (user->isConnected() == true && (lastPing >= PINGTIME))
			{
				displayActivity(user, "PING", SEND);
				user->sendMessage(user->formattedMessage("PING", user->getNickname(), ""));
				
				user->setConnected(false);
				user->setLastConnection(current);
				_start = current;
			}
			else
			{
				lastPing = (current.tv_sec - user->getLastConnection().tv_sec);

				if (user->isConnected() == false && lastPing >= TIMEOUT)
					disconnect(user);
			}
		}
	}
}

void	Server::run(void)
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
		if (poll(&_pollFds[0], _pollFds.size(), TIMEOUT * 1000) == -1)
			throw std::runtime_error("poll()");
			
		if (!_users.empty())
			checkConnection();
		
		for (size_t i = 0; i < _pollFds.size(); i++)
		{
			if (_pollFds[i].revents & POLLIN || _pollFds[i].revents & POLLOUT)
			{
				if (_pollFds[i].fd == _socketFd)
					newConnection();
				else
					receiveMessage(_pollFds[i]);
			}
		}
	}
}

void	Server::newConnection(void)
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

void	Server::receiveMessage(struct pollfd pfd)
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
			displayActivity(user, cmd, RECEIVE);
			
			copy.erase(0, pos + 2);
			user->parseMessage(cmd);
			user->execute();
		}
	}
}

User*		Server::findUserNickname(std::string nickname)
{
	std::map<int, User *>::iterator it = _users.begin();
	for (; it != _users.end(); ++it)
	{
		if (it->second->getNickname() == nickname)
		{
			return it->second;
		}
	}
	return NULL;
}

Channel*	Server::findChannel(std::string name)
{
	std::vector<Channel *>::iterator it = channels.begin();
	for (; it != channels.end(); ++it)
	{
		if ((*it)->getName() == name)
			return *it;
	}
	return NULL;
}

void	Server::disconnect(User* user)
{
	displayActivity(user, "DISCONNECT", SEND);

	std::vector<struct pollfd>::iterator it = _pollFds.begin();
	for (; it != _pollFds.end(); ++it)
	{
		if ((*it).fd == user->getFd())
			break;
	}
	
	_pollFds.erase(it);
	// close(user->getFd());
	_users.erase(user->getFd());
	delete user;
}

char*					Server::getPort(void) const
{
	return _port;
}

char*					Server::getPassword(void) const
{
	return _password;
}

std::map<int, User *>	Server::getUsers(void) const
{
	return _users;
}

char*					Server::getStartingTime(void) const
{
	return _startingTime;
}	

void					Server::eraseChannel(Channel* channel)
{
	std::vector<Channel *>::iterator it = channels.begin();
	for (; it != channels.end(); ++it)
	{
		if (*it == channel)
			break;
	}
	if (it != channels.end())
	{
		channels.erase(it);
		delete channel;
	}
}