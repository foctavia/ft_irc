/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:48:37 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/22 13:25:30 by foctavia         ###   ########.fr       */
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
				std::string	reason;
				if (args.size() > 2)
				{
					reason = accumulate(args, " ", 2);
					reason = reason.substr(1, reason.length() - 1);
				}
				channel->removeUser(user);
				user->leaveChannel(channel);
				channel->sendAll(user, user->formattedMessage("PART", reason, channel->getName()));
			}
		}
	}
}
