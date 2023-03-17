/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:29:05 by foctavia          #+#    #+#             */
/*   Updated: 2023/03/17 18:27:23 by foctavia         ###   ########.fr       */
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
