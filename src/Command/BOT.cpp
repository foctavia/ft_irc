/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BOT.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:12:53 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/24 11:26:19 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

void BOT(User *user)
{
	if (user->getServer()->findUserNickname("Felicia") != NULL)
	{
		displayActivity(user, "433: ERR_NICKNAMEINUSE", SEND);
		user->sendMessage(user->formattedReply("433", ERR_NICKNAMEINUSE("Felicia")));
		return ;
	}

	Bot *bot = new Bot;

	
}
