/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OPER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:08:41 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/20 14:48:29 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

/*
	Command: OPER
	Parameters: <username> <password>
*/

void	OPER(User *user)
{
	// std::cout << GREEN << "inside OPER" << RESET << std::endl;

	std::vector<std::string> args = user->getCommand()->getParameters();
	
	if (args.size() < 2)
	{
		displayActivity(user, "461: ERR_NEEDMOREPARAMS", SEND);
		user->sendMessage(user->formattedReply("461", ERR_NEEDMOREPARAMS("OPER")));
		return ;
	}

	User *userOper = NULL;
	std::map<int, User *> users = user->getServer()->getUsers();
	std::map<int, User *>::iterator it = users.begin();
	for (; it != users.end(); ++it)
	{
		if (it->second->getUsername() == args[0])
		{
			userOper = it->second;
			break;
		}
	}
	if (userOper == NULL)
		return ;
	
	if (args[1] != OPER_PASSWORD)
	{
		displayActivity(user, "464: ERR_PASSWDMISMATCH", SEND);
		user->sendMessage(user->formattedReply("464", ERR_PASSWDMISMATCH()));
		return ;
	}

	/*
		If the client is not connecting from a valid host for the given name,
		the server replies with an ERR_NOOPERHOST message and the request is not successful.
		--> Do we want to add an O-line configuration ?
	*/
	userOper->modes.at('o') = true;
	displayActivity(userOper, "381: RPL_YOUREOPER", SEND);
	userOper->sendMessage(userOper->formattedReply("381", RPL_YOUREOPER()));
	
}
