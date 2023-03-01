/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:21:20 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/01 11:20:26 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.h"

int ft_error(int type)
{
	if (type == ERR_ARGC)
		std::cerr << "wrong number of arguments provided\nusage: ./ircserv <port> <password>" << std::endl;
	
	return 1;
}