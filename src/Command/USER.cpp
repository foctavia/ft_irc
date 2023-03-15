/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:28:59 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/15 15:39:15 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

// USER sbeylot sbeylot localhost :Simon BEYLOT
// USER sbeylot sbeylot localhost :Simon BEYLOT
// USER <username> <hostname> <servername> <realname>

void	USER(User *user)
{
	std::cout << "\033[1;32minside USER\033[0m;" << std::endl;

	if (user->getStatus() == STATUS_VALID)
	{
		user->sendMessage(user->formattedMessage("462", ERR_ALREADYREGISTRED(), OPT_CODE));

		return ;
	}
	
	std::vector<std::string> args = user->getCommand()->getParameters();

	if (args.size() < 5 && args.at(3)[0] != ':')
	{
		user->sendMessage(user->formattedMessage("461", ERR_NEEDMOREPARAMS(user->getCommand()->getName()), OPT_CODE));
		return ;
	}

	user->setUsername(args.at(0));
	user->setHostname(args.at(1));
	user->setServername(args.at(2));

	std::string realname = std::accumulate(args.begin() + 3, args.end(), std::string(" "));
	realname.substr(1, realname.length());
	user->setRealname(realname);
	
	if (user->getStatus() == STATUS_PASS)
		user->setStatus(STATUS_USER);
	else if (user->getStatus() == STATUS_NICK)
	{
		user->setStatus(STATUS_VALID);
		user->sendMessage(user->formattedMessage("001", RPL_WELCOME(user), OPT_CODE));
	}
}
