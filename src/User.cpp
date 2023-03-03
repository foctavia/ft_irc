/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:38:52 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/03 16:02:42 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"


User::User( struct pollfd pfd, const char *address )
	: _valid(false), _address(address), _username(), _nickname(), _pfd(pfd)
{
	std::cout << "[SERVER]: accept new connection from " << _address
			<< " with fd " << _pfd.fd << std::endl;
}

User::~User()
{
	
}

/* GETTERS AND SETTERS */ 

std::string User::getUsername() const
{
	return _username;
}

std::string User::getNickname() const
{
	return _nickname;
}

Message User::getMessage() const
{
	return _message;
}

int User::getFd() const
{
	return _pfd.fd;
}

struct pollfd User::getPollFd() const
{
	return _pfd;
}

void User::setMessage(Message message)
{
	_message = message;	
}

void User::setPollFd(struct pollfd pfd)
{
	_pfd = pfd;	
}

void User::setUsername(std::string username)
{
	_username = username;
}

void User::setNickname (std::string nickname)
{
	_nickname = nickname;
}
		