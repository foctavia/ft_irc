/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:28:43 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/20 15:32:18 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

/*
	Command: NICK
	Parameters: <nickname>
*/

void	NICK(User *user)
{
	// std::cout << "\033[1;32minside NICK\033[0m;" << std::endl;

	if (user->getCommand()->getParameters().empty())
	{
		displayActivity(user, "431: ERR_NONICKNAMEGIVEN", SEND);
		user->sendMessage(user->formattedReply("431", ERR_NONICKNAMEGIVEN()));
		return ;
	}
		
	std::string nickname = user->getCommand()->getParameters()[0];	
	
	std::string special_characters("[]\\`_^{|}");
	if (!isalpha(nickname[0])
		&& (special_characters.find(nickname[0]) == std::string::npos))
	{
		displayActivity(user, "432: ERR_ERRONEUSNICKNAME", SEND);
		user->sendMessage(user->formattedReply("432", ERR_ERRONEUSNICKNAME(nickname)));
		return ;
	}
	
	if (nickname.length() > 9)
	{
		displayActivity(user, "432: ERR_ERRONEUSNICKNAME", SEND);
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
			displayActivity(user, "432: ERR_ERRONEUSNICKNAME", SEND);
			user->sendMessage(user->formattedReply("432", ERR_ERRONEUSNICKNAME(nickname)));
			return ;
		}
	}

	User *userExists = user->getServer()->findUserNickname(nickname);
	if (userExists != NULL)
	{
		displayActivity(user, "433: ERR_NICKNAMEINUSE", SEND);
		user->sendMessage(user->formattedReply("433", ERR_NICKNAMEINUSE(nickname)));
		return ;
	}
	
	user->setNickname(nickname);
	user->sendMessage(user->formattedMessage("NICK" , nickname, ""));
	

	if (user->getStatus() == STATUS_PASS)
		user->setStatus(STATUS_NICK);
	else if (user->getStatus() == STATUS_USER)
	{
		user->setStatus(STATUS_VALID);
		user->sendMessage(user->formattedReply("001", RPL_WELCOME(user)));
		user->sendMessage(user->formattedReply("002", RPL_YOURHOST()));
		user->sendMessage(user->formattedReply("003", RPL_CREATED(user)));
		user->sendMessage(user->formattedReply("004", RPL_MYINFO()));
		user->setConnected(true);
		displayActivity(user, "001: RPL_WELCOME", SEND);
		displayActivity(user, "002: RPL_YOURHOST", SEND);
		displayActivity(user, "003: RPL_CREATED", SEND);
		displayActivity(user, "004: RPL_MYINFO", SEND);
	}
}
