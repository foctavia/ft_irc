/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERRORS.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:34:00 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/15 12:47:19 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

std::string ERR_UNKNOWNCOMMAND(std::string command)
{
	return command + " :Unknown command";
}

std::string ERR_ERRONEUSNICKNAME(std::string nickname)
{
	return nickname + " :Erroneus nickname";
}

std::string	ERR_NONICKNAMEGIVEN(void)
{
	return ":No nickname given";
}

std::string	ERR_NEEDMOREPARAMS(std::string command)
{
	return command + ":Not enough parameters";
}

std::string	ERR_ALREADYREGISTRED(void)
{
	return ":You may not reregister";
}
