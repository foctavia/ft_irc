/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PONG.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 17:04:12 by foctavia          #+#    #+#             */
/*   Updated: 2023/03/17 10:46:24 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

/*
	Command: PONG
	Parameters: [<server>] <token>
*/

void	PONG(User *user)
{
	std::cout << "\033[1;32minside PONG\033[0m;" << std::endl;
	
	struct timeval	current;
	gettimeofday(&current, NULL);
	
	user->setConnected(true);
	// user->setLastConnection(current);

}