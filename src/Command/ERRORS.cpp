/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERRORS.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:34:00 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/21 18:24:54 by foctavia         ###   ########.fr       */
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

std::string	ERR_NICKNAMEINUSE(std::string nickname)
{
	return nickname + " :Nickname is already in use";
}

std::string	ERR_NONICKNAMEGIVEN(void)
{
	return ":No nickname given";
}

std::string	ERR_NEEDMOREPARAMS(std::string command)
{
	return command + " :Not enough parameters";
}

std::string	ERR_ALREADYREGISTRED(void)
{
	return ":You may not reregister";
}

std::string	ERR_NOSUCHNICK(std::string name)
{
	return name + " :No such nick/channel";
}

std::string	ERR_NOORIGIN(std::string name)
{
	return name + " :No origin specified";
}

std::string ERR_NOPRIVILEGES(std::string name)
{
	return name + " :Permission Denied- You're not an IRC operator";
}

std::string	ERR_PASSWDMISMATCH(void)
{
	return ":Password incorrect";
}

std::string	ERR_NOOPERHOST(void)
{
	return ":No O-lines for your host";
}

std::string	ERR_BADCHANMASK(std::string channel)
{
	return channel + " :Bad Channel Mask";
}

std::string	ERR_BADCHANNELKEY(std::string channel)
{
	return channel + " :Cannot join channel (+k)";
}

std::string	ERR_NOSUCHCHANNEL(std::string channel)
{
	return channel + " :No such channel";
}

std::string	ERR_USERSDONTMATCH(void)
{
	return ":Cannot change mode for other users";
}

std::string ERR_UMODEUNKNOWNFLAG(void)
{
	return ":Unknown MODE flag";
}

std::string ERR_UNKNOWNMODE(char c, std::string channel)
{
	std::string mode(1, c);
	
	return mode + " :is unknown mode char to me for " + channel;
}

std::string	ERR_NOTONCHANNEL(std::string channel)
{
	return channel + " :You're not on that channel";
}

std::string	ERR_USERNOTINCHANNEL(std::string nick, std::string channel)
{
	return nick + " " + channel + " :They aren't on that channel";
}
