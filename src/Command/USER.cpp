/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:28:59 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/14 16:59:14 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

void	USER(User *user)
{
	std::cout << "\033[1;32minside USER\033[0m;" << std::endl;

	size_t pos = 0;
	std::string param = user->getMessage()->getParameters();
	
	if ((pos = param.find(" ")) != std::string::npos)
		param.substr(0, pos);
	user->setUsername(param);
	
	if (user->getStatus() == STATUS_PASS)
		user->setStatus(STATUS_USER);
	else if (user->getStatus() == STATUS_NICK)
	{
		user->setStatus(STATUS_VALID);
		user->sendMessage(user->formattedMessage("", RPL_WELCOME(user)));
	}
}
