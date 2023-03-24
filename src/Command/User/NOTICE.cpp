/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NOTICE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:12:52 by foctavia          #+#    #+#             */
/*   Updated: 2023/03/23 16:08:57 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "irc.hpp"

/*
	Command: PRIVMSG
	Parameters: <target>{,<target>} <text to be sent>
*/

void	userNotice(User *user, std::string name, std::string message)
{
	User	*nickname = user->getServer()->findUserNickname(name);
	if (nickname == NULL)
		return ;
	displayActivity(user, user->formattedMessage("NOTICE", message, nickname->getNickname()), SEND);
	nickname->sendMessage(user->formattedMessage("NOTICE", message, nickname->getNickname()));
}

void	channelNotice(User *user, std::string name, std::string message)
{
	Channel *channel = user->getServer()->findChannel((name));
	if (channel == NULL)
		return ;
	else if (channel != NULL && !channel->modes['n'].empty() && !channel->isMember(user))
		return ;
	else if (channel != NULL && ((!channel->modes['m'].empty() && !channel->isOperator(user) && channel->modes['v'].empty())
		|| (!channel->modes['m'].empty() && !channel->isOperator(user) && !channel->modes['v'].empty() && !channel->hasVoicePrivilege(user))))
		return ;
	else if (channel != NULL && ((!channel->modes['b'].empty() && channel->isBanned(user) && channel->modes['e'].empty()) 
		|| (!channel->modes['b'].empty() && channel->isBanned(user) && !channel->modes['e'].empty() && !channel->isException(user))))
		return ;
	else if (channel != NULL && channel->isMember(user))
		channel->sendAll(user, user->formattedMessage("NOTICE", message, name));
}


void	NOTICE(User *user)
{
	
	std::vector<std::string>	args = user->getCommand()->getParameters();
	if (args[0].empty() || (args.size() < 2 && args.at(1)[0] != ':'))
		return ;

	if (!args[0].empty() && args.at(0)[0] == ':')
		return ;
	
	std::string	message = accumulate(args, " ", 1);
	message = message.substr(1, message.length() - 1);
	if (message.empty())
		return ;
	
	std::string channelPrefix("#");
	std::vector<std::string> targets = split(args.at(0), ",");
	for (std::vector<std::string>::iterator it = targets.begin(); it != targets.end(); ++it)
	{
		if (channelPrefix.find((*it)[0]) != std::string::npos)
			channelNotice(user, *it, message);
		else
			userNotice(user, *it, message);
		
	}
}