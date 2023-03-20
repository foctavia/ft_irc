/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:29:05 by foctavia          #+#    #+#             */
/*   Updated: 2023/03/20 12:53:44 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Channel.hpp"

Channel::Channel(void) { }

Channel::Channel(std::string name)
	: _name(name)
{
	
}

Channel::~Channel(void) { }

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
