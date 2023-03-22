/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INFO.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:00:32 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/22 14:21:56 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

void	INFO(User *user)
{

	displayActivity(user, "371: RPL_INFO", SEND);
	user->sendMessage(user->formattedReply("371", RPL_INFO("------- INFO -------")));
	user->sendMessage(user->formattedReply("371", RPL_INFO("Server is hosted locally.")));
	user->sendMessage(user->formattedReply("371", RPL_INFO("Version 1.0")));
	user->sendMessage(user->formattedReply("371", RPL_INFO("Made with \u2764 by:")));
	user->sendMessage(user->formattedReply("371", RPL_INFO(" - Simon <sbeylot>")));
	user->sendMessage(user->formattedReply("371", RPL_INFO(" - Fany <foctavia>")));
	user->sendMessage(user->formattedReply("371", RPL_INFO(" - Olivia <owalsh>")));
	user->sendMessage(user->formattedReply("371", RPL_INFO("Bye Feliciaaaa!")));
	user->sendMessage(user->formattedReply("372", RPL_ENDOFINFO()));
	displayActivity(user, "372: RPL_ENDOFINFO", SEND);

}
