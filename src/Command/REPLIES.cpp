/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   REPLIES.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:37:22 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/20 13:28:15 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

std::string RPL_WELCOME(User *user) 
{
	return ":Welcome to the Internet Relay Network " + user->getNickname() + "!" +
	user->getUsername() + "@localhost";
}

std::string RPL_YOURHOST(void) 
{
	return "Your host is localhost, running version 1.0";
}

std::string RPL_CREATED(User *user) 
{
	std::string time = user->getServer()->getStartingTime(); 
	return "This server was created " + time;
}

std::string RPL_MYINFO(User *user)
{
	return "localhost 1.0 <available user modes>
            	<available channel modes>";
}

std::string RPL_YOUREOPER() 
{
	return ":You are now an IRC operator ";
}
