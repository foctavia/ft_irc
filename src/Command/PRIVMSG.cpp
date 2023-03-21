/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:41:33 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/21 10:58:40 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

/*
	Command: PRIVMSG
	Parameters: <target>{,<target>} <text to be sent>
*/

void	PRIVMSG(User *user)
{
	// std::cout << "\033[1;32minside PRIVMSG\033[0m;" << std::endl;
	
	std::vector<std::string>	args = user->getCommand()->getParameters(); 
	if (!args[0].empty() && args.at(1)[0] != ':')
	{
		user->sendMessage(user->formattedReply("461", ERR_NEEDMOREPARAMS("")));
		return ;
	}


	// PRIVMSG oliv,#lol coucou
	
	std::string	message = accumulate(args, " ", 1);
	message = message.substr(1, message.length() - 1);
	
	std::string channelPrefix("#");

	std::vector<std::string> targets = split(args.at(0), ",");
	for (std::vector<std::string>::iterator it = targets.begin(); it != targets.end(); ++it)
	{
		if (channelPrefix.find((*it)[0]) != std::string::npos)
		{
			Channel *channel = user->getServer()->findChannel((*it));
			if (channel == NULL)
			{
				user->sendMessage(user->formattedReply("401", ERR_NOSUCHNICK("")));
				return ;
			}
			else if (channel != NULL && channel->isMember(user) && !channel->modes.at('a').empty())
				channel->sendAll(user, user->anonymousMessage("PRIVMSG", message, *it));
			else if (channel != NULL && channel->isMember(user))
				channel->sendAll(user, user->formattedMessage("PRIVMSG", message, *it));
		}
		else
		{

			User	*nickname = user->getServer()->findUserNickname(*it);
			if (nickname == NULL)
			{
				user->sendMessage(user->formattedReply("401", ERR_NOSUCHNICK("")));
				return ;
			}
			displayActivity(user, user->formattedMessage("PRIVMSG", message, nickname->getNickname()), SEND);
			nickname->sendMessage(user->formattedMessage("PRIVMSG", message, nickname->getNickname()));
		}
		
	}
}