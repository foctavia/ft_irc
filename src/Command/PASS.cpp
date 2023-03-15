/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:28:26 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/15 15:38:08 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	PASS(User *user)
{
	std::cout << "\033[1;32minside PASS\033[0m;" << std::endl;
	
	if (user->getStatus() > STATUS_NEW)
	{
		user->sendMessage(user->formattedMessage("462", ERR_ALREADYREGISTRED(), OPT_CODE));
		return ;
	}

	if (user->getCommand()->getParameters().empty())
	{
		user->sendMessage(user->formattedMessage("461", ERR_NEEDMOREPARAMS(user->getCommand()->getName()), OPT_CODE));
		return ;
	}

	std::string param = user->getCommand()->getParameters()[0];
	if (param == user->getServer()->getPassword())
	{
		std::cout << "\033[1;32mPassword is correct\033[0m;" << std::endl;
		if (user->getStatus() == STATUS_NEW)
			user->setStatus(STATUS_PASS);
	}	
}