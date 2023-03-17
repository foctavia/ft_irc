/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:28:59 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/17 15:47:17 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

/*
	Command: USER
	Parameters: <username> <hostname> <servername> <realname>
	Example: USER sbeylot sbeylot localhost :Simon BEYLOT
*/

void	USER(User *user)
{
	// std::cout << "\033[1;32minside USER\033[0m;" << std::endl;

	if (user->getStatus() == STATUS_VALID)
	{
		displayActivity(user, "462: ERR_ALREADYREGISTRED", SEND);
		user->sendMessage(user->formattedReply("462", ERR_ALREADYREGISTRED()));
		return ;
	}
	
	std::vector<std::string> args = user->getCommand()->getParameters();
	if (args.size() < 4 || args.at(3)[0] != ':' || (args.at(3)[0] && !args.at(3)[1]))
	{
		displayActivity(user, "461: ERR_NEEDMOREPARAMS", SEND);
		user->sendMessage(user->formattedReply("461", ERR_NEEDMOREPARAMS(user->getCommand()->getName())));
		return ;
	}

	user->setUsername(args.at(0));
	user->setHostname(args.at(1));
	user->setServername(args.at(2));

	std::string realname = accumulate(args, " ", 3);
	realname = realname.substr(1, realname.length());
	user->setRealname(realname);
	
	if (user->getStatus() == STATUS_PASS)
		user->setStatus(STATUS_USER);
	else if (user->getStatus() == STATUS_NICK)
	{
		user->setStatus(STATUS_VALID);
		user->sendMessage(user->formattedReply("001", RPL_WELCOME(user)));
		user->setConnected(true);

		displayActivity(user, "001: RPL_WELCOME", SEND);
	}
}
