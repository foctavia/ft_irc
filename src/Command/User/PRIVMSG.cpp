/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:41:33 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/23 16:09:24 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

/*
	Command: PRIVMSG
	Parameters: <target>{,<target>} <text to be sent>
	Example: oliv,#lol coucou
*/

void	userPrivMsg(User *user, std::string name, std::string message)
{
	User	*nickname = user->getServer()->findUserNickname(name);
	if (nickname == NULL)
	{
		displayActivity(user, "401: ERR_NOSUCHNICK", SEND);
		user->sendMessage(user->formattedReply("401", ERR_NOSUCHNICK("")));
		return ;
	}
	displayActivity(user, user->formattedMessage("PRIVMSG", message, nickname->getNickname()), SEND);
	nickname->sendMessage(user->formattedMessage("PRIVMSG", message, nickname->getNickname()));
}

void	channelPrivMsg(User *user, std::string name, std::string message)
{
	Channel *channel = user->getServer()->findChannel((name));
	if (channel == NULL)
	{
		displayActivity(user, "401: ERR_NOSUCHNICK", SEND);
		user->sendMessage(user->formattedReply("401", ERR_NOSUCHNICK("")));
		return ;
	}
	else if (channel != NULL && !channel->modes['n'].empty() && !channel->isMember(user))
	{
		displayActivity(user, "404: ERR_CANNOTSENDTOCHAN", SEND);
		user->sendMessage(user->formattedReply("404", ERR_CANNOTSENDTOCHAN(channel->getName())));
		return ;
	}
	else if (channel != NULL && ((!channel->modes['m'].empty() && !channel->isOperator(user) && channel->modes['v'].empty())
		|| (!channel->modes['m'].empty() && !channel->isOperator(user) && !channel->modes['v'].empty() && !channel->hasVoicePrivilege(user))))
	{
		displayActivity(user, "404: ERR_CANNOTSENDTOCHAN", SEND);
		user->sendMessage(user->formattedReply("404", ERR_CANNOTSENDTOCHAN(channel->getName())));
		return ;
	}
	else if (channel != NULL && ((!channel->modes['b'].empty() && channel->isBanned(user) && channel->modes['e'].empty()) 
		|| (!channel->modes['b'].empty() && channel->isBanned(user) && !channel->modes['e'].empty() && !channel->isException(user))))
	{
		displayActivity(user, "404: ERR_CANNOTSENDTOCHAN", SEND);
		user->sendMessage(user->formattedReply("404", ERR_CANNOTSENDTOCHAN(channel->getName())));
		return ;
	}
	else if (channel != NULL && channel->isMember(user))
		channel->sendAll(user, user->formattedMessage("PRIVMSG", message, name));
}

void	PRIVMSG(User *user)
{

	std::vector<std::string>	args = user->getCommand()->getParameters(); 
	if (args[0].empty() || (args.size() < 2 && args.at(1)[0] != ':'))
	{
		displayActivity(user, "461: ERR_NEEDMOREPARAMS", SEND);
		user->sendMessage(user->formattedReply("461", ERR_NEEDMOREPARAMS("")));
		return ;
	}

	if (!args[0].empty() && args.at(0)[0] == ':')
	{
		displayActivity(user, "411: ERR_NORECIPIENT", SEND);
		user->sendMessage(user->formattedReply("411", ERR_NORECIPIENT("PRIVMSG")));
		return ;
	}
	
	std::string	message = accumulate(args, " ", 1);
	message = message.substr(1, message.length() - 1);
	if (message.empty())
	{
		displayActivity(user, "412: ERR_NOTEXTTOSEND", SEND);
		user->sendMessage(user->formattedReply("412", ERR_NOTEXTTOSEND()));
		return ;
	}
	
	std::string channelPrefix("#");
	std::vector<std::string> targets = split(args.at(0), ",");
	for (std::vector<std::string>::iterator it = targets.begin(); it != targets.end(); ++it)
	{
		if (channelPrefix.find((*it)[0]) != std::string::npos)
		{
			channelPrivMsg(user, *it, message);
		}
		else
		{
			userPrivMsg(user, *it, message);
		}
		
	}
}