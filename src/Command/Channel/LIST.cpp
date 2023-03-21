/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LIST.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:48:29 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/21 19:24:02 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

/*
	Command: LIST
	Parameters: [ <channel> *( "," <channel> ) [ <target> ] ]
	--> we are not taking target into account, since we do not handle multi server
*/
void	LIST(User *user)
{
	std::cout << "\033[1;32minside LIST\033[0m;" << std::endl;

	std::vector<std::string> args = user->getCommand()->getParameters();

	if (!args.empty())
	{
		std::cout << "args size is " << args.size() << std::endl;
		std::cout << "args are not empty" << std::endl;
		std::cout << "args[0] = |" << args[0] << "|" << std::endl;
	}
	
	if (args.size() == 1 && args[0] == "")
	{
		std::vector<Channel *>::iterator it = user->channels.begin();
		for (; it != user->channels.end(); ++it)
		{
			user->sendMessage(user->formattedReply("322", RPL_LIST(*it)));
			displayActivity(user, "322: RPL_LIST", SEND);
		}
	}
	else
	{
		std::vector<std::string> channels = split(args.at(0), ",");
		std::vector<std::string>::iterator it = channels.begin();
		for (; it != channels.end(); ++it)
		{
			Channel *channelExists = user->getServer()->findChannel(*it);
			if (channelExists != NULL)
			{
				user->sendMessage(user->formattedReply("322", RPL_LIST(channelExists)));
				displayActivity(user, "322: RPL_LIST", SEND);
			}
		}
	}
	user->sendMessage(user->formattedReply("323", RPL_LISTEND()));
	displayActivity(user, "323: RPL_LISTEND", SEND);
}
