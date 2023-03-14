/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:28:43 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/14 16:59:02 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

void	NICK(User *user)
{
	std::cout << "\033[1;32minside NICK\033[0m;" << std::endl;

	size_t pos = 0;
	std::string nickname = user->getMessage()->getParameters();	
	if ((pos = nickname.find(" ")) != std::string::npos)
		nickname.substr(0, pos);

	if (nickname.empty())
	{
		std::cout << ERR_NONICKNAMEGIVEN() << std::endl;
		return ;
	}
		
	std::string special_characters("[]\\`_^{|}");
	if (!isalpha(nickname[0])
		&& (special_characters.find(nickname[0]) == std::string::npos))
	{
		std::cout << ERR_ERRONEUSNICKNAME(nickname) << std::endl;
		return ;
	}
	
	if (nickname.length() > 9)
	{
		std::cout << ERR_ERRONEUSNICKNAME(nickname) << std::endl;
		return ;
	}
		
	for (std::string::iterator it = nickname.begin() + 1; it != nickname.end(); ++it)
	{
		if (!isalpha(*it)
			&& !isdigit(*it)
			&& (special_characters.find(*it) == std::string::npos)
			&& *it != '-')
		{
			std::cout << ERR_ERRONEUSNICKNAME(nickname) << std::endl;
			return ;
		}
	}	
	
	user->setNickname(nickname);
	// std::cout << CORRECT_NICK(nickname) << std::endl;

	if (user->getStatus() == STATUS_PASS)
		user->setStatus(STATUS_NICK);
	else if (user->getStatus() == STATUS_USER)
	{
		user->setStatus(STATUS_VALID);
		user->sendMessage(RPL_WELCOME(user));
	}
}
