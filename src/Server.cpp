/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:26:02 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/01 10:51:21 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server( char *port, char *password )
	: _port(port), _password(password), _serverInfo(NULL), _socketFd(-1)
{
	std::cout << "constructing server with port " << _port << " and password " << _password << std::endl;
}

Server::~Server( void )
{
	clean();
}

void Server::clean( void )
{
	if (_serverInfo)
		freeaddrinfo(_serverInfo);
}

int	Server::createServer( void )
{
	struct addrinfo hints;
	int 			status;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	status = getaddrinfo(NULL, _port, &hints, &_serverInfo);
	if (status != 0)
		return ft_error(ERR_GETADDR);
	
	std::cout << "after getaddrinfo, status = " << status << std::endl;
	_socketFd = socket(_serverInfo->ai_family, _serverInfo->ai_socktype, _serverInfo->ai_protocol);
	std::cout << "server fd = " << _socketFd << std::endl;
	if (_socketFd < 0)
		return ft_error(ERR_SOCKET_OPENING);

	bind(_socketFd, _serverInfo->ai_addr, _serverInfo->ai_addrlen);
	return 0;
}
