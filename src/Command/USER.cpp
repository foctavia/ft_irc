/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:28:59 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/15 12:01:11 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

// USER sbeylot sbeylot localhost :Simon BEYLOT
// USER <username> <hostname> <servername> <realname>

void	USER(User *user)
{
	std::cout << "\033[1;32minside USER\033[0m;" << std::endl;

	if (user->getStatus() == STATUS_VALID)
	{
		std::cout << ERR_ALREADYREGISTRED() << std::endl;
		return ;
	}
	
	size_t pos = 0;
	std::string param = user->getMessage()->getParameters();
	std::string arg;
	int arg_count = 0;
	while ((pos = param.find(" ")) != std::string::npos && arg_count < 3)
	{
		arg = param.substr(0, pos);
		param.erase(0, pos + 1);
		if (arg_count == 0)
			user->setUsername(arg);
		if (arg_count == 1)
			user->setHostname(arg);
		if (arg_count == 2)
			user->setServername(arg);
		arg_count++;
	}
	if (arg_count != 3 && (pos = param.find(":")) == std::string::npos)
	{
		std::cout << ERR_NEEDMOREPARAMS("USER") << std::endl;
		return ;
	}
	arg = param.substr(1, param.length() - 1);
	user->setRealname(arg);
	
	
	if (user->getStatus() == STATUS_PASS)
		user->setStatus(STATUS_USER);
	else if (user->getStatus() == STATUS_NICK)
	{
		user->setStatus(STATUS_VALID);
		user->sendMessage(user->formattedMessage("001", RPL_WELCOME(user), OPT_CODE));
	}
}
