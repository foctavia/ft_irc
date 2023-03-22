/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:48:24 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/21 18:59:42 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

/*
	Command: KICK
	Parameters: <channel> *( "," <channel> ) <user> *( "," <user> ) [<comment>]
*/

void	KICK(User *user)
{
	// std::cout << "\033[1;32minside KICK\033[0m;" << std::endl;

	std::vector<std::string> args = user->getCommand()->getParameters();

	if (args.size() < 2)
	{
		displayActivity(user, "461: ERR_NEEDMOREPARAMS", SEND);
		user->sendMessage(user->formattedReply("461", ERR_NEEDMOREPARAMS("OPER")));
		return ;
	}

	std::string channelPrefix("#");

	std::vector<std::string> channels = split(args.at(0), ",");
	for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); ++it)
	{
		if (channelPrefix.find((*it)[0]) != std::string::npos)
		{
			Channel *channel = user->getServer()->findChannel((*it));
			if (channel == NULL)
			{
				user->sendMessage(user->formattedReply("403", ERR_NOSUCHCHANNEL(*it)));
				displayActivity(user, "403: ERR_NOSUCHCHANNEL", SEND);
				return ;
			}
			if (channel != NULL && !channel->isMember(user))
			{
				user->sendMessage(user->formattedReply("442", ERR_NOTONCHANNEL(*it)));
				displayActivity(user, "442: ERR_NOTONCHANNEL", SEND);
				return ;
			}
			if (channel != NULL && !user->isChannelOperator(channel))
			{
				user->sendMessage(user->formattedReply("482", ERR_CHANOPRIVSNEEDED(channel->getName())));
				displayActivity(user, "482: ERR_CHANOPRIVSNEEDED", SEND);
				return ;
			}
			if (channel != NULL)
			{
				std::vector<std::string> targets = split(args.at(1), ",");
				for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); ++it)
				{
					User	*target = user->getServer()->findUserNickname(*it);
					if (target != NULL)
					{
						if (!channel->isMember(target))
						{
							user->sendMessage(user->formattedReply("441", ERR_USERNOTINCHANNEL(target->getNickname(), channel->getName())));
							displayActivity(user, "441: ERR_USERNOTINCHANNEL", SEND);
							return ;
						}
						else
						{
							std::string	reason;
							if (args.size() > 2)
							{
								reason = accumulate(args, " ", 2);
								reason = reason.substr(1, reason.length() - 1);
							}
							channel->removeMember(target);
							channel->removeOperator(target);
							channel->removeInvite(target);
							target->leaveChannel(channel);
							channel->sendAll(user, user->formattedMessage("KICK", reason, channel->getName() + " " + target->getNickname()));
						}
					}
				}
			}
		}
	}

}
