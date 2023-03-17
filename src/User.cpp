/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:38:52 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/17 10:04:42 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"


User::User(struct pollfd pfd, const char *address, Server *server)
	: _address(address), _username(), _nickname(), _realname(), _pfd(pfd), _command(new Command()), _server(server), _status(STATUS_NEW)
{
	displayTime();
	std::cout << "[SERVER]: accept new connection from " << _address
			<< " with fd " << _pfd.fd << std::endl;
}

User::~User(void)
{
	delete _command;
}

/* GETTERS AND SETTERS */ 

std::string	User::getUsername(void) const
{
	return _username;
}

std::string	User::getNickname(void) const
{
	return _nickname;
}

int	User::getFd(void) const
{
	return _pfd.fd;
}

struct pollfd	User::getPollFd(void) const
{
	return _pfd;
}

Server	*User::getServer(void) const 
{
	return _server;
}

int	User::getStatus(void) const
{
	return _status;
}

void	User::setStatus(int status)
{
	_status = status;
}


void	User::setPollFd(struct pollfd pfd)
{
	_pfd = pfd;	
}

void	User::setUsername(std::string username)
{
	_username = username;
}

void	User::setNickname(std::string nickname)
{
	_nickname = nickname;
}

std::string	User::getHostname(void) const
{
	return _hostname;
}

void	User::setHostname(std::string hostname)
{
	_hostname = hostname;
}

std::string	User::getServername(void) const
{
	return _servername;
}

void	User::setServername(std::string servername)
{
	_servername = servername;
}

std::string	User::getRealname(void) const
{
	return _realname;
}

void	User::setRealname(std::string realname)
{
	_realname = realname;
}

Command	*User::getCommand() const
{
	return _command;
}

struct timeval	User::getLastConnection(void) const
{
	return _lastConnection;
}

bool	User::isConnected(void) const
{
	return _connected;
}

void	User::setLastConnection(struct timeval connection)
{
	_lastConnection = connection;
}

void	User::setConnected(bool value)
{
	_connected = value;	
}

/* MODIFIERS */

void	User::parseMessage(std::string input)
{	
	std::vector<std::string> values = split(input, " ");
	
	_command->setName(values[0]);

	if (values.size() > 1)
	{
		values.erase(values.begin());
		_command->setParameters(values);
	}
}

std::string	User::formattedReply(std::string code, std::string argument)
{
	std::string reply;
	
	if (_status == STATUS_VALID)
		reply += updatedId() + code + " " + _nickname + " " + argument + "\r\n";
		
	return reply;
}

std::string	User::formattedMessage(std::string command, std::string argument, std::string target)
{
	std::string formatted;
	
	if (_status > STATUS_PASS)
	{
		formatted += updatedId() + command;
		if (!target.empty())
			formatted += " " + target;
		formatted += " :" + argument + "\r\n";
	}
	
	return formatted;
}

std::string	User::updatedId(void)
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

void	User::execute()
{
	if (_command->availableCommands.find(_command->getName()) != _command->availableCommands.end())
		_command->availableCommands[_command->getName()](this);
	else
		displayActivity(NULL, "command " + _command->getName() + " not found!", NONE);
}
