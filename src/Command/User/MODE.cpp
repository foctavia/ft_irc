/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:31:43 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/23 16:08:43 by foctavia         ###   ########.fr       */
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
	std::string flags = "ovimnpstkl+-";

	if (flags.find(c) != std::string::npos)
		return true;
	return false;
}

bool	unknownFlagChecker(User *user, std::string parameter)
{
	for (std::string::iterator it = parameter.begin(); it != parameter.end(); ++it)
	{
		if (!knownUserFlags(*it))
		{
			user->sendMessage(user->formattedReply("501", ERR_UMODEUNKNOWNFLAG()));
			displayActivity(user, "501: ERR_UMODEUNKNOWNFLAG", SEND);
			return true;
		}
	}
	return false;
}

bool	unknownFlagChecker(User *user, Channel *channel, char c)
{
	if (!knownChannelFlags(c))
	{
		user->sendMessage(user->formattedReply("472", ERR_UNKNOWNMODE(c, channel->getName())));
		displayActivity(user, "472: ERR_UNKNOWNMODE", SEND);
		return true;
	}
	return false;
}

void	userMode(User *user)
{
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

size_t		countFlagsNeedingParams(std::string flags)
{
	std::string	requireParams = "ovklbeI";
	int 		params = 0;
	
	bool sign = true;
	for (std::string::iterator it = flags.begin(); it != flags.end(); ++it)
	{
		if (*it == '+')
			sign = true;
		else if (*it == '-')
			sign = false;
		else if (sign == true && requireParams.find(*it) != std::string::npos)
			params++;
		else if (sign == false && (*it == 'v' || *it == 'o' || *it == 'k'))
			params++;
	}
	return params;
}

bool	checkParamsMatchFlags(size_t nbParams, std::vector<std::string> args)
{
	if (args.size() - 2 != nbParams)
		return false;
	return true;
}

void	checkSign(char c, bool *sign)
{
	if (c == '+')
		*sign = true;
	else if (c == '-')
		*sign = false;
}

void	toggleMode(char c, bool sign, Channel *target)
{
	if (c == 'p' || c == 's' || c == 'i'
		|| c == 't' || c == 'm' || c == 'n')
	{
		if (sign == true)
		{
			if ((c == 'p' && !target->modes['s'].empty())
				|| (c == 's' && !target->modes['p'].empty()))
				return ;
			target->modes[c] = std::string(1, c);
		}
		else
			target->modes[c].clear();
	}
}

void	setMode(User *user, Channel *channel, char flag, bool sign, std::vector<std::string> args, int *i)
{
	if (flag != 'l' && flag != 'k' && flag != 'o' && flag != 'v')
		return ;
	if (sign == false)
	{	
		if (flag == 'k')
		{
			if (args[*i] == channel->getKey())
				channel->modes[flag].clear();
		}
		else if (flag == 'l')
			channel->modes[flag].clear();
		else if (flag == 'o' || flag == 'v')
		{
			User *target = user->getServer()->findUserNickname(args[*i]);
			if (target == NULL)
			{
				displayActivity(user, "401: ERR_NOSUCHNICK", SEND);
				user->sendMessage(user->formattedReply("401", ERR_NOSUCHNICK(args[*i])));
				return ;
			}
			channel->modes[flag].clear();
			flag == 'v' ? channel->removeVoicePrivilege(target) : channel->removeOperator(target);
			(*i)++;
		}
	}
	else
	{
		if (flag == 'k' && !channel->modes['k'].empty())
		{
			displayActivity(user, "467: ERR_KEYSET", SEND);
			user->sendMessage(user->formattedReply("467", ERR_KEYSET(channel->getName())));
			return ;
		}
		else if (flag == 'l' || flag == 'k')
			flag == 'l' ? channel->setMaxUsers(atoi(args[*i].c_str())) : channel->setKey(args[*i]);
		else if (flag == 'o' || flag == 'v')
		{
			User *target = user->getServer()->findUserNickname(args[*i]);
			if (target == NULL)
			{
				displayActivity(user, "401: ERR_NOSUCHNICK", SEND);
				user->sendMessage(user->formattedReply("401", ERR_NOSUCHNICK(args[*i])));
				return ;
			}
			else if (!channel->isMember(target))
			{
				 	user->sendMessage(user->formattedReply("442", ERR_NOTONCHANNEL(user->getNickname())));
					displayActivity(user, "442: ERR_NOTONCHANNEL", SEND);
					return ;
			}
			if (flag == 'v')
				channel->voicePrivileges.push_back(target);
			else if (flag == 'o')
				channel->operators.push_back(target);
		}
		channel->modes[flag] = std::string(1, flag);
		(*i)++;
	}
	
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
	
	
	if (args.size() == 1)
	{
		user->sendMessage(user->formattedReply("324", RPL_CHANNELMODEIS(user, target)));
		displayActivity(user, "324: RPL_CHANNELMODEIS", SEND);
		return ;
	}
	
	if (!user->isChannelOperator(target))
	{
		user->sendMessage(user->formattedReply("482", ERR_CHANOPRIVSNEEDED(target->getName())));
		displayActivity(user, "482: ERR_CHANOPRIVSNEEDED", SEND);
		return ;
	}
	
	size_t nbParams = countFlagsNeedingParams(args[1]);
	
	if (checkParamsMatchFlags(nbParams, args) == false)
	{
		displayActivity(user, "461: ERR_NEEDMOREPARAMS", SEND);
		user->sendMessage(user->formattedReply("461", ERR_NEEDMOREPARAMS("MODE")));
		return ;
	}
	
	bool sign = true;
	std::string::iterator it = args[1].begin();
	for (int i = 2; it != args[1].end(); ++it)
	{
		if (unknownFlagChecker(user, target, *it) == true)
			continue ;
		else
		{
			checkSign(*it, &sign);
			toggleMode(*it, sign, target);
			setMode(user, target, *it, sign, args, &i);
		}
	}
	user->sendMessage(user->formattedReply("324", RPL_CHANNELMODEIS(user, target)));
	displayActivity(user, "324: RPL_CHANNELMODEIS", SEND);
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
