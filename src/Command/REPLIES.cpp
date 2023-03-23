/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   REPLIES.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:37:22 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/23 15:30:55 by foctavia         ###   ########.fr       */
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
	return "localhost 1.0 aiwro ovimnpstklbeI";
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

std::string RPL_CHANNELMODEIS(User *user, Channel *channel)
{
	std::string mode = channel->getName() + " +";

	std::map<char, std::string>::iterator it = channel->modes.begin();
	for (; it != channel->modes.end(); ++it)
	{
		if (!it->second.empty())
			mode += it->first;
	}
	if (user->isChannelMember(channel))
	{
		if (!channel->modes['k'].empty())
			mode += " " + channel->getKey();
		if (!channel->modes['l'].empty())
		{
			std::stringstream stream;
			stream << channel->getMaxUsers();
			std::string maxusers;
			stream >> maxusers;
			mode += " " + maxusers;
		}
	}
	return mode;
}

// = #lll :@simon
std::string RPL_NAMREPLY(Channel *channel)
{
	std::string reply;

	if (!channel->modes['s'].empty())
		reply += '@';
	else if (!channel->modes['p'].empty())
		reply += '*';
	else
		reply += '=';
	
	reply += " " + channel->getName();
	reply += " :";

	std::vector<User *>::iterator it = channel->members.begin();
	for (; it != channel->members.end(); ++it)
	{
		if (it != channel->members.begin())
			reply += " ";
		if ((*it)->isChannelOperator(channel))
			reply += "@";
		else
			reply += " ";
		reply += (*it)->getNickname();
	}
	return reply;	
}

// #lll :End of /NAMES list
std::string RPL_ENDOFNAMES(std::string channel)
{
	return channel + " :End of /NAMES list";
}

std::string ERR_CHANOPRIVSNEEDED(std::string channel)
{
	return channel + " :You're not channel operator";
}

std::string RPL_TOPIC(Channel *channel)
{
	return channel->getName() + " :" + channel->getTopic();
}

std::string RPL_NOTOPIC(std::string channel)
{
	return channel + " :No topic is set";
}

std::string RPL_LIST(Channel *channel)
{
	std::string reply;
	
	reply += channel->getName() + " ";
	
	std::stringstream stream;
    stream << channel->members.size();
	std::string client_count;
    stream >> client_count;

	reply += client_count;
	reply += " :";
	reply += channel->getTopic();
	return reply;	
}

std::string RPL_LISTEND(void)
{
	return " :End of /LIST";	
}

std::string RPL_INVITING(std::string channel, std::string nick)
{
	return channel + " " + nick;	
}

std::string RPL_INFO(std::string string)
{
	return string;	
}

std::string RPL_ENDOFINFO(void)
{
	return " :End of INFO list";	
}

std::string RPL_TIME(void)
{
	std::time_t	now = std::time(0);
	std::string currentTime = ctime(&now);
	return "localhost :" + currentTime;	
}

std::string RPL_VERSION(void)
{
	return "1.0 localhost :yo";	
}
