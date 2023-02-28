/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:21:20 by owalsh            #+#    #+#             */
/*   Updated: 2023/02/28 18:27:03 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.h"

int ft_error(int type)
{
	if (type == ERR_ARGC)
		std::cout << "wrong number of arguments provided\nusage: ./ircserv <port> <password>" << std::endl;
	if (type == ERR_GETADDR)
		perror("getaddrinfo");
	if (type == ERR_SOCKET_OPENING)
		std::cout << "Error opening socket" << std::endl;
	
	return 1;
}