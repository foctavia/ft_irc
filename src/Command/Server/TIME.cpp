/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TIME.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:00:27 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/22 14:57:41 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

void	TIME(User *user)
{
	displayActivity(user, "391: RPL_TIME", SEND);
	user->sendMessage(user->formattedReply("391", RPL_TIME()));
}
