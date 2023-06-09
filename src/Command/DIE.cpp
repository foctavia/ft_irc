/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DIE.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:05:06 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/23 17:01:58 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

extern bool g_running;

void	DIE(User *user)
{
	if (user->modes['o'] == false)
		return ;
	if (user->modes['o'] == true)
		g_running = false;
}
