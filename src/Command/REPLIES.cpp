/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   REPLIES.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:37:22 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/15 15:11:04 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

std::string RPL_WELCOME(User *user) 
{
	return ":Welcome to the Internet Relay Network " + user->getNickname() + "!" +
	user->getUsername() + "@localhost";
}
