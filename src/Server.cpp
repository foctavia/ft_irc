/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:26:02 by owalsh            #+#    #+#             */
/*   Updated: 2023/02/28 18:26:22 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(void) { }

Server::~Server(void)
{
	clean();
}

void Server::clean()
{
	if (_serverInfo)
		freeaddrinfo(_serverInfo);
}

int	Server::createServer(char *port, char *password)
{
	struct addrinfo hints;
	int 			status;

	std::cout << "constructing server with port " << port << " and password " << password << std::endl;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	
	memset(_serverInfo, 0, sizeof *_serverInfo);
	_serverInfo = NULL;
	status = getaddrinfo(NULL, port, &hints, &_serverInfo);
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
