/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:48:27 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/22 11:51:02 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

/*
	Command: INVITE
	Parameters: <nickname> <channel>
*/

void	INVITE(User *user)
{
	std::cout << "\033[1;32minside INVITE\033[0m;" << std::endl;

	std::vector<std::string> args = user->getCommand()->getParameters();

	if (args.size() < 2)
	{
		displayActivity(user, "461: ERR_NEEDMOREPARAMS", SEND);
		user->sendMessage(user->formattedReply("461", ERR_NEEDMOREPARAMS("OPER")));
		return ;
	}

	Channel *channel = user->getServer()->findChannel(args[1]);
	if (channel == NULL)
		return ;

	if (!channel->modes['i'].empty() && !user->isChannelOperator(channel))
	{
		user->sendMessage(user->formattedReply("482", ERR_CHANOPRIVSNEEDED(channel->getName())));
		displayActivity(user, "482: ERR_CHANOPRIVSNEEDED", SEND);
		return ;
	}

	if (!user->isChannelMember(channel))
	{
		user->sendMessage(user->formattedReply("442", ERR_NOTONCHANNEL(user->getNickname())));
		displayActivity(user, "442: ERR_NOTONCHANNEL", SEND);
		return ;
	}

	User *guest = user->getServer()->findUserNickname(args[0]);
	if (guest == NULL)
	{
		user->sendMessage(user->formattedReply("401", ERR_NOSUCHNICK("")));
		displayActivity(user, "401: ERR_NOSUCHNICK", SEND);
		return ;
	}

	if (guest->isChannelMember(channel))
	{
		user->sendMessage(user->formattedReply("443", ERR_USERONCHANNEL(guest->getNickname(), channel->getName())));
		displayActivity(user, "443: ERR_USERONCHANNEL", SEND);
		return ;
	}

	guest->sendMessage(user->formattedMessage("INVITE", channel->getName(), guest->getNickname()));

	user->sendMessage(user->formattedReply("341", RPL_INVITING(guest->getNickname(),channel->getName())));
	displayActivity(user, "341: RPL_INVITING", SEND);

	
}
