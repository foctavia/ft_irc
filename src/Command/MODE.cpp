/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:31:43 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/22 17:28:23 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

bool	knownUserFlags(char c)
{
	std::string flags = "aiwroO+-";

	if (flags.find(c) != std::string::npos)
		return true;
	return false;
}

bool	knownChannelFlags(char c)
{
	std::string flags = "OovaimnqpsrtklbeI+-";

	if (flags.find(c) != std::string::npos)
		return true;
	return false;
}

bool	unknownFlagChecker(User *user, std::string parameter)
{
	for (std::string::iterator it = parameter.begin(); it != parameter.end(); ++it)
	{
		if (!knownUserFlags(*it) )
		{
			user->sendMessage(user->formattedReply("501", ERR_UMODEUNKNOWNFLAG()));
			displayActivity(user, "501: ERR_UMODEUNKNOWNFLAG", SEND);
			return true;
		}
	}
	return false;
}

bool	unknownFlagChecker(User *user, Channel *channel, std::string parameter)
{
	for (std::string::iterator it = parameter.begin(); it != parameter.end(); ++it)
	{
		if (!knownChannelFlags(*it))
		{
			user->sendMessage(user->formattedReply("472", ERR_UNKNOWNMODE(*it, channel->getName())));
			displayActivity(user, "472: ERR_UNKNOWNMODE", SEND);
			return true;
		}
	}
	return false;
}

void	userMode(User *user)
{
	std::cout << GREEN << "In user MODE" << RESET << std::endl;
	
	std::vector<std::string> args = user->getCommand()->getParameters();

	User *target = user->getServer()->findUserNickname(args[0]); 
	if (target != user)
	{
		user->sendMessage(user->formattedReply("502", ERR_USERSDONTMATCH()));
		displayActivity(user, "502: ERR_USERSDONTMATCH", SEND);
		return ;
	}
	
	if (args.size() == 1)
	{
		user->sendMessage(user->formattedReply("221", RPL_UMODEIS(user)));
		displayActivity(user, "221: UMODEIS", SEND);
		return ;
	}
	
	if (unknownFlagChecker(user, args[1]))
		return ;
	
	bool sign = true;
	for (std::string::iterator it = args[1].begin(); it != args[1].end(); ++it)
	{
		char c = *it;
		if (c == '+')
			sign = true;
		else if (c == '-')
			sign = false;
		else if (c == 'i' || c == 'w')
			user->modes.at(c) = sign;
	}

	user->sendMessage(user->formattedReply("221", RPL_UMODEIS(user)));
	displayActivity(user, "221: UMODEIS", SEND);	
}

size_t		countFlagsNeedingKeys(std::string flags)
{
	std::string	requireKeys = "klovb";
	int 		keys = 0;
	
	for (std::string::iterator it = flags.begin(); it != flags.end(); ++it)
	{
		if (requireKeys.find(*it) != std::string::npos)
			keys++;
	}
	return keys;
}

bool	checkKeysMatchFlags(size_t nbKeys, std::vector<std::string> args)
{
	if (args.size() - 2 != nbKeys)
		return false;
	return true;
}

void	channelMode(User *user)
{
	std::vector<std::string> args = user->getCommand()->getParameters();
	
	Channel *target = user->getServer()->findChannel(args[0]);
	if (target == NULL)
	{
		user->sendMessage(user->formattedReply("403", ERR_NOSUCHCHANNEL(args[0])));
		displayActivity(user, "403: ERR_NOSUCHCHANNEL", SEND);
		return ;
	}
	
	if (!target->modes['n'].empty() && !user->isChannelMember(target))
	{
		user->sendMessage(user->formattedReply("442", ERR_NOTONCHANNEL(user->getNickname())));
		displayActivity(user, "442: ERR_NOTONCHANNEL", SEND);
		return ;
	}
	
	if (args.size() == 1)
	{
		user->sendMessage(user->formattedReply("324", RPL_CHANNELMODEIS(target)));
		displayActivity(user, "324: RPL_CHANNELMODEIS", SEND);
		return ;
	}
	

	if (unknownFlagChecker(user, target, args[1]))
		return ;

	
	size_t nbKeys = countFlagsNeedingKeys(args[1]);
	if (checkKeysMatchFlags(nbKeys, args) == false)
	{
		return ;
	}
	
	
	bool sign = true;
	int i = 0;
	for (std::string::iterator it = args[1].begin(); it != args[1].end(); ++it, i++)
	{
		char c = *it;
		if (c == '+')
			sign = true;
		else if (c == '-')
			sign = false;
		else if (c == 'p' || c == 's' || c == 'i' || c == 't')
		{
			if (sign == true)
			{
				if ((c == 'p' && target->modes['s'].empty())
					|| (c == 's' && target->modes['p'].empty())
					|| c == 'i')
					target->modes[c] = std::string(1, c);
			}
			else
				target->modes[c].clear();
		}
		else if (c == 'l')
		{
			if (sign == true)
			{
				target->modes[c] = std::string(1, c);
				target->setMaxUsers(99);
			}
			else
				target->modes[c].clear();
		}
		else if (c == 'I') // list invitation masks
		{
			
		}
		
	}
}

bool isChannel(std::string target)
{
	std::string prefix = "#";

	if (prefix.find(target[0]) != std::string::npos)
		return true;
	return false;
}

/*
	Command: MODE
	Parameters: <target>
        *( ( "+" / "-" ) *( "i" / "w" / "o" / "O" / "r" ) )
	
	MODE Angel +i-w 

*/

void	MODE(User *user)
{
	std::vector<std::string> args = user->getCommand()->getParameters();

	if (args.empty())
	{
		displayActivity(user, "461: ERR_NEEDMOREPARAMS", SEND);
		user->sendMessage(user->formattedReply("461", ERR_NEEDMOREPARAMS("OPER")));
		return ;
	}

	std::string target = args[0];

	if (isChannel(target))
		return channelMode(user);
	return userMode(user);
}
