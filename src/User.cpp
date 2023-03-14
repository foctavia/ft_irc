/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:38:52 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/14 13:24:29 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"


User::User( struct pollfd pfd, const char *address, Server *server )
	: _address(address), _username(), _nickname(), _pfd(pfd), _message(new Message(pfd.fd)), _server(server), _status(STATUS_NEW)
{
	std::cout << "[SERVER]: accept new connection from " << _address
			<< " with fd " << _pfd.fd << std::endl;
}

User::~User()
{
	delete _message;
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

int User::getFd() const
{
	return _pfd.fd;
}

struct pollfd User::getPollFd() const
{
	return _pfd;
}

Server*	User::getServer() const { return _server; }

int	User::getStatus() const { return _status; }

void	User::setStatus(int status)
{
	_status = status;
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


/* MODIFIERS */ 

void User::parseMessage()
{	
	std::string raw_message = input;
	std::string delimiter = " ";
	
	size_t pos = 0;
	
	pos = raw_message.find(delimiter);
	if (pos == std::string::npos)
	{
		_message->setCommand(raw_message.substr(0, raw_message.length()));
		std::cout << "[PARSING]: message only contains one command: " << _message->getCommand() << std::endl;
		return ;
	}

	// command = raw_message.substr(0, pos);
	_message->setCommand(raw_message.substr(0, pos));
	raw_message.erase(0, pos + delimiter.length());
	_message->setParameters(raw_message);
	
	std::cout << "[PARSING]: message command: " << _message->getCommand();
	std::cout << " parameters: " << _message->getParameters() << std::endl;

	
	
}

std::string		User::formattedMessage(std::string command, std::string argument)
{
	std::string formatted;

	formatted += ":";
	
	if (_status == STATUS_VALID)
		formatted += _nickname + "!" + _username + "@localhost ";
	formatted += command + " :" + argument;
	return formatted;
}


Message* User::getMessage() const
{
	return _message;
}
