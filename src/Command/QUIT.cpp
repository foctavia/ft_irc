/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:59:56 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/15 15:11:04 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	QUIT(User *user)
{
	std::cout << "\033[1;32minside QUIT\033[0m;" << std::endl;
	if (send(user->getFd(), "\n", 2, MSG_NOSIGNAL) == -1)
		perror("send");
	user->getServer()->disconnect(user);
}
