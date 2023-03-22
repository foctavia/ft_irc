/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NAMES.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:48:32 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/22 15:26:32 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

/*
	Command: NAMES
	Parameters: [ <channel> *( "," <channel> ) [ <target> ] ]
*/

void	NAMES(User *user)
{
	// std::cout << "\033[1;32minside NAMES\033[0m;" << std::endl;

	std::vector<std::string> args = user->getCommand()->getParameters();
	if (args.empty())
		return ;
	
	
	std::vector<std::string> channels = split(args.at(0), ",");

	std::vector<std::string>::iterator it = channels.begin();
	for (; it != channels.end(); ++it)
	{
		Channel *channel = user->getServer()->findChannel(*it);
		if (channel != NULL && channel->modes['s'].empty())
		{
			user->sendMessage(user->formattedReply("353", RPL_NAMREPLY(channel)));
			displayActivity(user, "353: RPL_NAMREPLY", SEND);

		}
		user->sendMessage(user->formattedReply("366", RPL_ENDOFNAMES(*it)));
		displayActivity(user, "366: RPL_ENDOFNAMES", SEND);
	}
	
}
