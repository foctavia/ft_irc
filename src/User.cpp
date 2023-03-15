/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:38:52 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/15 11:41:17 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"


User::User( struct pollfd pfd, const char *address, Server *server )
	: _address(address), _username(), _nickname(), _realname(), _pfd(pfd), _message(new Message(pfd.fd)), _server(server), _status(STATUS_NEW)
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

std::string		User::getHostname(void) const
{
	return _hostname;
}

void			User::setHostname(std::string hostname)
{
	_hostname = hostname;
}

std::string		User::getServername(void) const
{
	return _servername;
}

void			User::setServername(std::string servername)
{
	_servername = servername;
}

std::string		User::getRealname(void) const
{
	return _realname;
}

void			User::setRealname(std::string realname)
{
	_realname = realname;
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

std::string		User::formattedMessage(std::string command, std::string argument, int option)
{
	std::string formatted;
	
	if (_status > STATUS_PASS) {
		formatted += updatedId();
		if (option == OPT_COMMAND)
			formatted += command + " :" + argument + "\r\n";
		else if (option == OPT_CODE)
			formatted += command + " " + _nickname + " " + argument + "\r\n";
	}
	return formatted;
}

std::string		User::updatedId()
{
	std::string formatted;

	formatted += ":";
	if (_status > STATUS_PASS)
		formatted += _nickname + "!" + _username + "@localhost ";
	return formatted;
}


void	User::sendMessage(std::string message)
{
	if (_status > STATUS_PASS)
	{
		if (send(getFd(), message.c_str(), message.length(), MSG_NOSIGNAL) == -1)
			perror("send");
	}
}


Message* User::getMessage() const
{
	return _message;
}
