/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:28:43 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/16 11:05:14 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	NICK(User *user)
{
	std::cout << "\033[1;32minside NICK\033[0m;" << std::endl;

	if (user->getCommand()->getParameters().empty())
	{
		user->sendMessage(user->formattedReply("431", ERR_NONICKNAMEGIVEN()));
		return ;
	}
		
	std::string nickname = user->getCommand()->getParameters()[0];	
	
	std::string special_characters("[]\\`_^{|}");
	if (!isalpha(nickname[0])
		&& (special_characters.find(nickname[0]) == std::string::npos))
	{
		user->sendMessage(user->formattedReply("432", ERR_ERRONEUSNICKNAME(nickname)));
		return ;
	}
	
	if (nickname.length() > 9)
	{
		user->sendMessage(user->formattedReply("432", ERR_ERRONEUSNICKNAME(nickname)));
		return ;
	}
		
	for (std::string::iterator it = nickname.begin() + 1; it != nickname.end(); ++it)
	{
		if (!isalpha(*it)
			&& !isdigit(*it)
			&& (special_characters.find(*it) == std::string::npos)
			&& *it != '-')
		{
			user->sendMessage(user->formattedReply("432", ERR_ERRONEUSNICKNAME(nickname)));
			return ;
		}
	}	
	
	user->setNickname(nickname);
	user->sendMessage(user->formattedMessage("NICK" , nickname, ""));
	

	if (user->getStatus() == STATUS_PASS)
		user->setStatus(STATUS_NICK);
	else if (user->getStatus() == STATUS_USER)
	{
		user->setStatus(STATUS_VALID);
		user->sendMessage(user->formattedReply("001", RPL_WELCOME(user)));
	}
}
