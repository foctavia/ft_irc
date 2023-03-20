/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   REPLIES.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:37:22 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/20 18:02:25 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

std::string RPL_WELCOME(User *user) 
{
	return ":Welcome to the Internet Relay Network " + user->getNickname() + "!" +
	user->getUsername() + "@localhost";
}

std::string RPL_YOURHOST(void) 
{
	return "Your host is localhost, running version 1.0";
}

std::string RPL_CREATED(User *user) 
{
	std::string time = user->getServer()->getStartingTime(); 
	return "This server was created " + time;
}

std::string RPL_MYINFO(void)
{
	return "localhost 1.0 aiwroO OovaimnqpsrtklbeI";
}

std::string RPL_YOUREOPER() 
{
	return ":You are now an IRC operator ";
}

std::string RPL_UMODEIS(User *user)
{
	std::string mode = "+";

	std::map<char, bool>::iterator it = user->modes.begin();
	for (; it != user->modes.end(); ++it)
	{
		if (it->second == true)
			mode += it->first;
	}
	return mode;
}

std::string RPL_CHANNELMODEIS(Channel *channel)
{
	std::string mode = channel->getName() + " +";

	std::map<char, std::string>::iterator it = channel->modes.begin();
	for (; it != channel->modes.end(); ++it)
	{
		if (!it->second.empty())
			mode += it->first;
	}
	return mode;
}
