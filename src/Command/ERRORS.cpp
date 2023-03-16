/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERRORS.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:34:00 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/16 17:20:10 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

std::string	ERR_UNKNOWNCOMMAND(std::string command)
{
	return command + " :Unknown command";
}

std::string	ERR_ERRONEUSNICKNAME(std::string nickname)
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

std::string	ERR_NOSUCHNICK(std::string name)
{
	return name + ":No such nick/channel";
}

std::string	ERR_NOORIGIN(std::string name)
{
	return name + ":No origin specified";
}
