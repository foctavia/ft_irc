/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PING.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:10:47 by foctavia          #+#    #+#             */
/*   Updated: 2023/03/23 16:09:08 by foctavia         ###   ########.fr       */
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
