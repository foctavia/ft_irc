/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:29:05 by foctavia          #+#    #+#             */
/*   Updated: 2023/03/22 19:29:39 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Channel.hpp"

Channel::Channel(void)
	: _topic(""), _max_users(0)
{
	modes.insert(std::make_pair('O', ""));
	modes.insert(std::make_pair('o', ""));
	modes.insert(std::make_pair('v', ""));
	modes.insert(std::make_pair('a', ""));
	modes.insert(std::make_pair('i', ""));
	modes.insert(std::make_pair('m', ""));
	modes.insert(std::make_pair('n', "n"));
	modes.insert(std::make_pair('q', ""));
	modes.insert(std::make_pair('p', ""));
	modes.insert(std::make_pair('s', ""));
	modes.insert(std::make_pair('r', ""));
	modes.insert(std::make_pair('t', ""));
	modes.insert(std::make_pair('k', ""));
	modes.insert(std::make_pair('l', ""));
	modes.insert(std::make_pair('b', ""));
	modes.insert(std::make_pair('e', ""));
	modes.insert(std::make_pair('I', ""));
}

Channel::~Channel(void)
{
	members.clear();
	invites.clear();
	operators.clear();
	modes.clear();
}

std::string	Channel::getName(void) const
{
	return _name;
}

std::string Channel::getKey(void) const
{
	return _key;
}

std::string Channel::getMask(void) const
{
	return _mask;
}

int			Channel::getMaxUsers(void) const
{
	return _max_users;
}

std::string	Channel::getTopic(void) const
{
	return _topic;
}

void		Channel::setName(std::string name)
{
	_name = name;
}

void		Channel::setKey(std::string key)
{
	modes.at('k') = key;
	_key = key;
}

void		Channel::setMask(std::string mask)
{
	_mask = mask;
}

void		Channel::setMaxUsers(int max)
{
	_max_users = max;
}

void		Channel::setTopic(std::string topic)
{
	_topic = topic;
}


void		Channel::sendAll(User *user, std::string message)
{
	for (std::vector<User *>::iterator it = members.begin(); it != members.end(); ++it)
	{
		if (*it != user)
		{
			(*it)->sendMessage(message);
			displayActivity(*it, message, SEND);
		}
	}
}

bool		Channel::isMember(User *user)
{
	for (std::vector<User *>::iterator it = members.begin(); it != members.end(); ++it)
	{
		if (*it == user)
			return true;
	}
	return false;
}

bool		Channel::isOperator(User *user)
{
	for (std::vector<User *>::iterator it = operators.begin(); it != operators.end(); ++it)
	{
		if (*it == user)
			return true;
	}
	return false;
}

bool		Channel::isInvite(User *user)
{
	for (std::vector<User *>::iterator it = invites.begin(); it != invites.end(); ++it)
	{
		if (*it == user)
			return true;
	}
	return false;
}

bool		Channel::isBanned(User *user)
{
	for (std::vector<User *>::iterator it = banned.begin(); it != banned.end(); ++it)
	{
		if (*it == user)
			return true;
	}
	return false;
}

bool		Channel::isException(User *user)
{
	for (std::vector<User *>::iterator it = exceptions.begin(); it != exceptions.end(); ++it)
	{
		if (*it == user)
			return true;
	}
	return false;
}

bool		Channel::hasVoicePrivilege(User *user)
{
	for (std::vector<User *>::iterator it = voicePrivilages.begin(); it != voicePrivilages.end(); ++it)
	{
		if (*it == user)
			return true;
	}
	return false;
}

void		Channel::removeMember(User *user)
{
	std::vector<User *>::iterator it = members.begin();
	for (; it != members.end(); ++it)
	{
		if (*it == user)
		{
			members.erase(it);
			break ;
		}
	}
}

void		Channel::removeOperator(User *user)
{
	std::vector<User *>::iterator it = operators.begin();
	for (; it != operators.end(); ++it)
	{
		if (*it == user)
		{
			operators.erase(it);
			break ;
		}
	}
}

void		Channel::removeInvite(User *user)
{
	std::vector<User *>::iterator it = invites.begin();
	for (; it != invites.end(); ++it)
	{
		if (*it == user)
		{
			invites.erase(it);
			break ;
		}
	}
}

void		Channel::removeBan(User *user)
{
	std::vector<User *>::iterator it = banned.begin();
	for (; it != banned.end(); ++it)
	{
		if (*it == user)
		{
			banned.erase(it);
			break ;
		}
	}
}

void		Channel::removeException(User *user)
{
	std::vector<User *>::iterator it = exceptions.begin();
	for (; it != exceptions.end(); ++it)
	{
		if (*it == user)
		{
			exceptions.erase(it);
			break ;
		}
	}
}

void		Channel::removeVoicePrivilege(User *user)
{
	std::vector<User *>::iterator it = voicePrivilages.begin();
	for (; it != voicePrivilages.end(); ++it)
	{
		if (*it == user)
		{
			voicePrivilages.erase(it);
			break ;
		}
	}
}

void		Channel::removeUser(User *user)
{
	removeMember(user);
	removeOperator(user);
	removeInvite(user);
	removeBan(user);
	removeException(user);
	removeVoicePrivilege(user);
}
