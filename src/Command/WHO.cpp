/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WHO.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:04:37 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/22 16:25:01 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	WHO(User *user)
{
	std::vector<std::string args = user->getCommand()->getParameters();

	if (agrs.empty())
		return ;
	if (args[0][0] == '#')
	{
		Channel *target = user->getServer()->findChannel(args[0])
		if (target == NULL)
		{
			user->sendMessage(user->formattedReply("403", ERR_NOSUCHCHANNEL(args[0])));
			displayActivity(user, "403: ERR_NOSUCHCHANNEL", SEND);
			return ;
		}
		std::vector<User *>::iterator it = target->menbers.begin();
		for (; it != target->menbers.end(); ++it)
		{
			if (*it != user && (*it)->modes['i'] == false)
				user->sendMessage(user->formattedReply("352", RPL_WHOREPLY(user, target, *it)))
		}
		
		
		
	}
}