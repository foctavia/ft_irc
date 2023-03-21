/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:48:34 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/21 14:58:26 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

void	TOPIC(User *user)
{
	std::cout << "\033[1;32minside TOPIC\033[0m;" << std::endl;

	std::vector<std::string> args = user->getCommand()->getParameters();

	if (args.empty())
	{
		displayActivity(user, "461: ERR_NEEDMOREPARAMS", SEND);
		user->sendMessage(user->formattedReply("461", ERR_NEEDMOREPARAMS("OPER")));
		return ;
	}

	Channel *target = user->getServer()->findChannel(args[0]);
	if (target == NULL)
	{
		user->sendMessage(user->formattedReply("442", ERR_NOTONCHANNEL(args[0])));
		displayActivity(user, "442: ERR_NOTONCHANNEL", SEND);
		return ;
	}
	
	if (!target->modes['s'].empty())
		return ;
	
	if (!target->modes['n'].empty() && !user->isChannelMember(target))
	{
		user->sendMessage(user->formattedReply("442", ERR_NOTONCHANNEL(user->getNickname())));
		displayActivity(user, "442: ERR_NOTONCHANNEL", SEND);
		return ;
	}

	if (!target->modes['t'].empty() && !user->isChannelOperator(target))
	{
		user->sendMessage(user->formattedReply("482", ERR_CHANOPRIVSNEEDED(target->getName())));
		displayActivity(user, "482: ERR_CHANOPRIVSNEEDED", SEND);
		return ;
	}
	
	if (args.size() == 1 && !target->getTopic().empty())
	{
		user->sendMessage(user->formattedReply("332", RPL_TOPIC(target)));
		displayActivity(user, "332: RPL_TOPIC", SEND);
		return ;
	}

	if (args.size() == 1 && target->getTopic().empty())
	{
		user->sendMessage(user->formattedReply("331", RPL_NOTOPIC(target->getName())));
		displayActivity(user, "331: RPL_NOTOPIC", SEND);
		return ;
	}

	if (args[1][0] != ':')
		return ;
	
	std::string topic = accumulate(args, " ", 1);
	topic = topic.substr(1, topic.length() - 1);
	
	std::cout << "topic to be set as = " << topic << std::endl;
	
	target->setTopic(topic);
	
	if (topic.empty())
		target->sendAll(user, user->formattedReply("331", RPL_NOTOPIC(target->getName())));
	else
		target->sendAll(user, user->formattedReply("332", RPL_TOPIC(target)));
	
	
}
