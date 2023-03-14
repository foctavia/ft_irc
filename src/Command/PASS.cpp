/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:28:26 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/14 16:59:08 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

void	PASS(User *user)
{
	if (user->getStatus() > STATUS_NEW)
	{
		std::cout << ERR_UNKNOWNCOMMAND(user->getMessage()->getCommand()) << std::endl;
		return ;
	}
	std::cout << "\033[1;32minside PASS\033[0m;" << std::endl;

	size_t pos = 0;
	std::string param = user->getMessage()->getParameters();
	
	if ((pos = param.find(" ")) != std::string::npos)
		param.substr(0, pos);
	if (param == user->getServer()->getPassword())
	{
		std::cout << "\033[1;32mPassword is correct\033[0m;" << std::endl;
		if (user->getStatus() == STATUS_NEW)
			user->setStatus(STATUS_PASS);
	}	
}