/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PING.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:10:47 by foctavia          #+#    #+#             */
/*   Updated: 2023/03/24 10:42:19 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

/*
	Command: PING
	Parameters: <token>
*/

void	PING(User *user)
{
	
	if (user->getCommand()->getParameters().empty())
	{
		user->sendMessage(user->formattedReply("409", ERR_NOORIGIN(user->getNickname())));
		return ;
	}
	
	displayActivity(user, "PONG", SEND);
	user->sendMessage(user->formattedMessage("PONG", user->getNickname(), ""));
}

void	BOT(User *user)
{
	std::cout <<"possible" << std::endl;
	(void)user;

}