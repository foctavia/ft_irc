/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:29:05 by foctavia          #+#    #+#             */
/*   Updated: 2023/03/20 19:05:37 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Channel.hpp"

Channel::Channel(void)
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

void		Channel::sendAll(User *user, std::string message)
{
	displayActivity(user, message, SEND);
	for (std::vector<User *>::iterator it = members.begin(); it != members.end(); ++it)
	{
		if (*it != user)
			(*it)->sendMessage(message);
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
