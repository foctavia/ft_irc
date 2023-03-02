/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:26:02 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/02 12:22:29 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server( char *port, char *password )
	: _port(port), _password(password), _socketInfo(NULL), _socketFd(-1)
{
	std::cout << "constructing server with port " << _port << " and password " << _password << std::endl;
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

void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
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
	}

	addSocket(_socketFd);

	struct sockaddr_storage clientAddress;
	socklen_t				addressLength;
	int 					newFd;
 	char remoteIP[INET6_ADDRSTRLEN];
	char buf[256];
	
	while (1)
	{
		if (poll(&_pollFds[0], _pollFds.size(), TIMEOUT) == -1)
			throw std::runtime_error("poll()");

		std::vector<struct pollfd>::iterator it = _pollFds.begin();
		for (size_t i = 0; i < _pollFds.size(); i++, it++)
		{
			if (_pollFds[i].revents & POLLIN)
			{
				if (_pollFds[i].fd == _socketFd)
				{
					addressLength = sizeof clientAddress;
					newFd = accept(_socketFd, (struct sockaddr *)&clientAddress, &addressLength);
					if (newFd == -1)
						throw std::runtime_error("accept()");
					else
					{
						addSocket(newFd);
						std::cout << "pollserver: new connection from " << inet_ntop(clientAddress.ss_family,
                                get_in_addr((struct sockaddr*)&clientAddress),
                                remoteIP, INET6_ADDRSTRLEN)
								<< " with fd " << newFd << std::endl;
					}
				}
				else
				{
					int nbytes = recv(_pollFds[i].fd, buf, sizeof buf, 0);
					int sender_fd = _pollFds[i].fd;
					if (nbytes <= 0)
					{
						if (nbytes == 0)
							std::cout << "pollserver: socket hung up" << std::endl;
						else
							perror("recv");
						
						close(_pollFds[i].fd);
						_pollFds[i].fd = -1;
					}
					else
					{
						for (size_t j = 0; j < _pollFds.size(); j++)
						{
							int dest_fd = _pollFds[j].fd;

							if (dest_fd != _socketFd && dest_fd != sender_fd)
							{
								if (send(dest_fd, buf, nbytes, 0) == -1)
									perror("send");
							} 
						}	
					}
					
					
				}
			}
		}
	}
}

char	*Server::getPort( void ) const
{
	return _port;
}

char	*Server::getPassword( void ) const
{
	return _password;
}
