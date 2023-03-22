/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VERSION.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:00:23 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/22 15:13:58 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

void	VERSION(User *user)
{
	displayActivity(user, "351: RPL_VERSION", SEND);
	user->sendMessage(user->formattedReply("351", RPL_VERSION()));
}
