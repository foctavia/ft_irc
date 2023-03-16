/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:41:33 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/16 11:09:03 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

// PRIVMSG <receiver>{,<receiver>} :<text to be sent>

void	PRIVMSG(User *user)
{
	std::cout << "\033[1;32minside PRIVMSG\033[0m;" << std::endl;
	
	std::vector<std::string>	args = user->getCommand()->getParameters(); 
	if (!args[0].empty() && args.at(0)[0] == ':')
	{
		user->sendMessage(user->formattedReply("401", ERR_NOSUCHNICK("")));
		return ;
	}

	std::string	message = accumulate(args, " ", 1);
	message = message.substr(1, message.length() - 1);

	std::vector<std::string>	recipients = split(args.at(0), ",");
	for (std::vector<std::string>::iterator it = recipients.begin(); it != recipients.end(); ++it)
	{
		User	*target = user->getServer()->checkUser(*it);
		if (target == NULL)
		{
			user->sendMessage(user->formattedReply("401", ERR_NOSUCHNICK("")));
			return ;
		}

		std::cout << user->formattedMessage("PRIVMSG", message, target->getNickname()) << std::endl;
		target->sendMessage(user->formattedMessage("PRIVMSG", message, target->getNickname()));
		
	}
}