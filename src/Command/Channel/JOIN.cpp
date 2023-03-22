/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:31:08 by foctavia          #+#    #+#             */
/*   Updated: 2023/03/22 10:22:37 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

Channel*	createChannel(User *user, std::string name, std::string key)
{
	Channel *channel = new Channel;
	
	if (name.length() > 50)
	{
		displayActivity(user, "476: ERR_BADCHANMASK", SEND);
		user->sendMessage(user->formattedReply("476", ERR_BADCHANMASK(name)));
		delete channel;
		return NULL;
	}
	
	std::string prefix("#");
	if (prefix.find(name[0]) == std::string::npos)
	{
		displayActivity(user, "476: ERR_BADCHANMASK", SEND);
		user->sendMessage(user->formattedReply("476", ERR_BADCHANMASK(name)));
		delete channel;
		return NULL;
	}
	
	for (std::string::iterator it = name.begin() + 1; it != name.end(); ++it)
	{
		if (*it == ' ' || *it == 7)
		{
			displayActivity(user, "476: ERR_BADCHANMASK", SEND);
			user->sendMessage(user->formattedReply("476", ERR_BADCHANMASK(name)));
			delete channel;
			return NULL;
		}
		if (*it == ':')
		{
			std::vector<std::string> channelInfo = split(name, ":");
			name = channelInfo[0];
			channel->setMask(channelInfo[1]);
			break ;
			// what if there are more than one ':' ?
		}
	}
	
	channel->setName(name);
	if (!key.empty())
		channel->setKey(key);
	channel->members.push_back(user);
	channel->operators.push_back(user);
	user->channels.push_back(channel);	
	user->getServer()->channels.push_back(channel);
	return channel;
}

/*
	Command: JOIN
	Parameters: ( <channel> *( "," <channel> ) [ <key> *( "," <key> ) ] ) / "0"
*/

void	JOIN(User *user)
{
	std::vector<std::string> args = user->getCommand()->getParameters();
	 
	if (args.empty())
	{
		displayActivity(user, "461: ERR_NEEDMOREPARAMS", SEND);
		user->sendMessage(user->formattedReply("461", ERR_NEEDMOREPARAMS("OPER")));
		return ;
	}

	std::vector<std::string> channels = split(args.at(0), ",");
	std::vector<std::string> keys;
	if (args.size() > 1)
		keys = split(args.at(1), ",");

	size_t i = 0;
	for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); ++it, ++i)
	{
		Channel *channelExists = user->getServer()->findChannel(*it);
		if (channelExists == NULL)
		{
			if (keys.size() > i)
				channelExists = createChannel(user, *it, keys[i]);
			else
				channelExists = createChannel(user, *it, "");
		}
		else
		{
			if (!channelExists->getKey().empty())
			{
				if (keys.size() <= i || keys[i] != channelExists->getKey())
				{
					displayActivity(user, "475: ERR_BADCHANNELKEY", SEND);
					user->sendMessage(user->formattedReply("475", ERR_BADCHANNELKEY("OPER")));
					return ;
				}
			}
			
			channelExists->sendAll(user, user->formattedMessage("JOIN", channelExists->getName(), ""));
			user->channels.push_back(channelExists);
			channelExists->members.push_back(user);
		}

// if (topic.empty())
// 		target->sendAll(user, user->formattedReply("331", RPL_NOTOPIC(target->getName())));
// 	else
		// target->sendAll(user, user->formattedReply("332", RPL_TOPIC(target)));
		if (channelExists != NULL)
		{
			if (channelExists->getTopic().empty())
				user->sendMessage(user->formattedReply("331", RPL_NOTOPIC(channelExists->getName())));
			else
				user->sendMessage(user->formattedReply("332", RPL_TOPIC(channelExists)));
			NAMES(user);
		}
	}
}
