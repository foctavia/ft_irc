/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 10:58:17 by foctavia          #+#    #+#             */
/*   Updated: 2023/03/24 11:36:17 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

Bot::Bot(char *port, char *password, char *nick)
	: _port(port), _password(password), _nick(nick)
{ }

Bot::~Bot(void)
{
	close(_socketFd);
}

int	Bot::getListenerSocket(void)
{
	int				listenerFd = -1;
	int				yes = 1;
	int 			status = 0;
	struct addrinfo hints, *tmp;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	status = getaddrinfo("127.0.0.1", _port, &hints, &_serverInfo);
	if (status != 0)
		throw std::runtime_error("getaddrinfo()");

	for (tmp = _serverInfo; tmp != NULL; tmp = tmp->ai_next)
	{
		listenerFd = socket(tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol);
		if (listenerFd < 0)
			continue ;
			
		if (connect(listenerFd, tmp->ai_addr, tmp->ai_addrlen) == -1)
		{
			close(listenerFd);
			listenerFd = -1;
			continue ;
		}
		
		break ;
	}

	if (tmp == NULL)
		throw std::runtime_error("failed to connect bot");
		
	freeaddrinfo(_serverInfo);
	_serverInfo = NULL;

	return listenerFd;
}

void	Bot::run(void)
{
	try
	{
		_socketFd = getListenerSocket();
	}
	catch(const std::exception& e)
	{
		std::cerr << "ERROR: " << e.what() << std::endl;
		return ;
	}

	char buffer[512];
	memset(buffer, 0, sizeof buffer);

	int nbytes = recv(_socketFd, buffer, sizeof buffer, 0);

	if (nbytes == -1)
		throw std::runtime_error("recv()");
	else
		std::cout << "bot receive: " << buffer << std::endl;
	
}