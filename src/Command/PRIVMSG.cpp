/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:41:33 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/15 17:10:40 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

// PRIVMSG <receiver>{,<receiver>} :<text to be sent>

void	PRIVMSG(User *user)
{
	std::cout << "\033[1;32minside PRIVMSG\033[0m;" << std::endl;
	
	std::vector<std::string>	args = user->getCommand()->getParameters(); 
	for (std::vector<std::string>::iterator it = args.begin(); it != args.end(); ++it)
		std::cout << " " << *it;
	std::cout << std::endl;
	
	if (!args[0].empty() && args.at(0)[0] == ':')
	{
		user->sendMessage(user->formattedMessage("401", ERR_NOSUCHNICK(""), OPT_CODE));
		return ;
	}

	
	std::string	message = std::accumulate(args.begin() + 1, args.end(), std::string(" "));
	message.substr(2, message.length());
	std::cout << "message : |" << message << "|" << std::endl;

	std::vector<std::string>	recipients = split(args.at(0), ",");
	for (std::vector<std::string>::iterator it = recipients.begin(); it != recipients.end(); ++it)
	{
		User	*target = user->getServer()->checkUser(*it);
		if (target == NULL)
		{
			user->sendMessage(user->formattedMessage("401", ERR_NOSUCHNICK(""), OPT_CODE));
			return ;
		}
		std::cout << "target nickname: " << target->getNickname() << std::endl;
		// std::string fullMessage = target->getNickname() + " :";
		std::cout << user->formattedMessage("PRIVMSG " + target->getNickname(), message, OPT_COMMAND) << std::endl;
		target->sendMessage(user->formattedMessage("PRIVMSG", message, OPT_COMMAND));
		
	}
}