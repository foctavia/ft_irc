/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:29:05 by foctavia          #+#    #+#             */
/*   Updated: 2023/03/23 15:58:13 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Channel.hpp"

Channel::Channel(void)
	: _topic(""), _maxUsers(0)
{
	modes.insert(std::make_pair('o', ""));
	modes.insert(std::make_pair('v', ""));
	modes.insert(std::make_pair('i', ""));
	modes.insert(std::make_pair('m', ""));
	modes.insert(std::make_pair('n', "n"));
	modes.insert(std::make_pair('p', ""));
	modes.insert(std::make_pair('s', ""));
	modes.insert(std::make_pair('t', ""));
	modes.insert(std::make_pair('k', ""));
	modes.insert(std::make_pair('l', ""));
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

size_t		Channel::getMaxUsers(void) const
{
	return _maxUsers;
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

void		Channel::setMaxUsers(size_t max)
{
	_maxUsers = max;
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
	for (std::vector<User *>::iterator it = voicePrivileges.begin(); it != voicePrivileges.end(); ++it)
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
	std::vector<User *>::iterator it = voicePrivileges.begin();
	for (; it != voicePrivileges.end(); ++it)
	{
		if (*it == user)
		{
			voicePrivileges.erase(it);
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
