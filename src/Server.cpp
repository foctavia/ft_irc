/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:26:02 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/01 14:53:48 by foctavia         ###   ########.fr       */
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
		_pollFds[i].close(_pollFds[i].fd);
		i++;
	}
	_pollFds.clear();
}

// void	Server::createSocket( void )
// {
// 	struct addrinfo hints;
// 	int 			status;

// 	memset(&hints, 0, sizeof hints);
// 	hints.ai_family = AF_UNSPEC;
// 	hints.ai_socktype = SOCK_STREAM;
// 	hints.ai_flags = AI_PASSIVE;

// 	status = getaddrinfo(NULL, _port, &hints, &_socketInfo);
// 	if (status != 0)
// 		throw std::runtime_error("getaddrinfo()");
	
// 	std::cout << "after getaddrinfo, status = " << status << std::endl;
// 	_socketFd = socket(_socketInfo->ai_family, _socketInfo->ai_socktype, _socketInfo->ai_protocol);
// 	std::cout << "server fd = " << _socketFd << std::endl;
// 	if (_socketFd < 0)
// 		throw std::runtime_error("socket opening");

// 	bind(_socketFd, _socketInfo->ai_addr, _socketInfo->ai_addrlen);
// }

void	Server::getListenerSocket( void )
{
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
		_socketFd = socket(_socketInfo->ai_family, _socketInfo->ai_socktype, _socketInfo->ai_protocol);
		if (_socketFd < 0)
			continue ;
			
		if (setsockopt(_socketFd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
			throw std::runtime_error("setsockopt()");

		if (bind(_socketFd, _socketInfo->ai_addr, _socketInfo->ai_addrlen) < 0)
		{
			close(_socketFd);
			continue ;
		}
		
		break ;
	}
	
	freeaddrinfo(_socketInfo);
	_socketInfo = NULL;

	if (tmp = NULL)
		throw std::runtime_error("failed to bind the socket");

	if (listen(_socketFd, BACKLOG) == -1)
		throw std::runtime_error("failed to listen to the socket")
}

void	Server::addSocket( void )
{
	if (_socketFd == -1)
		return ;

	struct pollfd	tmp;
	
	tmp.fd = _socketFd;
	tmp.events = POLLIN;
	
	_pollFds.push_back(tmp);
}

void	Server::run( void )
{
	try
	{
		getListenerSocket();
	}
	catch(const std::exception &e)
	{
		std::cerr << "ERROR: " << e.what() << std::endl;
	}

	addSocket();

	while (1)
	{
		int	poll_count = poll(_pollFds, _pollFds.size(), TIMEOUT);

		if (poll_count == -1)
			throw std::runtime_error("poll()");

		for (std::vector<pollfd>::iterator it = _pollFds.begin(); it != _pollFds.end(); ++it)
		{
			
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
