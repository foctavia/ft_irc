/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:48:37 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/21 17:19:57 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

void	PART(User *user)
{
	std::vector<std::string> args = user->getCommand()->getParameters();

	if (args.empty())
	{
		displayActivity(user, "461: ERR_NEEDMOREPARAMS", SEND);
		user->sendMessage(user->formattedReply("461", ERR_NEEDMOREPARAMS("OPER")));
		return ;
	}

	std::string channelPrefix("#");

	std::vector<std::string> targets = split(args.at(0), ",");
	for (std::vector<std::string>::iterator it = targets.begin(); it != targets.end(); ++it)
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
			else if (channel != NULL && !channel->isMember(user))
			{
				user->sendMessage(user->formattedReply("442", ERR_NOTONCHANNEL(*it)));
				displayActivity(user, "442: ERR_NOTONCHANNEL", SEND);
				return ;
			}
			else
			{
				channel->removeMember(user);
				channel->removeOperator(user);
				channel->removeInvite(user);
				user->leaveChannel(channel);
				user->sendMessage(user->formattedMessage("PART", "", channel->getName()));
				channel->sendAll(user, user->formattedMessage("PART", "", channel->getName()));
				// displayActivity(user, user->formattedMessage("PART", "", channel->getName()), SEND);
			}
		}
	}
}
