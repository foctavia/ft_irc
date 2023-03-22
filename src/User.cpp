/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:38:52 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/22 14:43:58 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"


User::User(struct pollfd pfd, const char *address, Server *server)
	: _address(address), _username(), _nickname(), _realname(), _pfd(pfd), _command(new Command()), _server(server), _status(STATUS_NEW)
{
	displayTime();
	std::cout << "[SERVER] " << BOLD << ITALIC << "accept new connection from " << _address
			<< " with fd " << _pfd.fd << RESET << std::endl;
	modes.insert(std::make_pair('a', false));
	modes.insert(std::make_pair('i', false));
	modes.insert(std::make_pair('w', true));
	modes.insert(std::make_pair('r', false));
	modes.insert(std::make_pair('o', false));
	modes.insert(std::make_pair('O', false));
}

User::~User(void)
{

	std::vector<Channel *>::iterator it = channels.begin();
	for (; it != channels.end(); ++it)
	{
		(*it)->removeMember(this);
		(*it)->removeOperator(this);
		(*it)->removeInvite(this);
		sendMessage(formattedMessage("PART", "", (*it)->getName()));
		(*it)->sendAll(this, formattedMessage("PART", "", (*it)->getName()));
	}
	channels.clear();
	close(_pfd.fd);
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
	_command->clear();
	
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
	
	reply += updatedId() + code + " " + _nickname + " " + argument + "\r\n";
	return reply;
}

std::string	User::anonymousMessage(std::string command, std::string argument, std::string target)
{
	std::string formatted;

	if (_status >= STATUS_PASS)
	{
		formatted += "anonymous!anonymous@anonymous. " + command;
		if (!target.empty())
			formatted += " " + target;
		formatted += " :" + argument + "\r\n";
	}
	
	return formatted;
}

std::string	User::formattedMessage(std::string command, std::string argument, std::string target)
{
	std::string formatted;
	
	if (_status >= STATUS_PASS)
	{
		formatted += updatedId() + command;
		if (!target.empty())
			formatted += " " + target;
		if (!argument.empty())
			formatted += " :" + argument;
		formatted += "\r\n";
			
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
	if (send(getFd(), message.c_str(), message.length(), MSG_NOSIGNAL) == -1)
		perror("send");
}

void	User::execute()
{
	if (_command->availableCommands.find(_command->getName()) != _command->availableCommands.end())
		_command->availableCommands[_command->getName()](this);
	else
		displayActivity(NULL, "command " + _command->getName() + " not found!", NONE);
}

bool	User::isChannelOperator(Channel *channel)
{
	std::vector<User *>::iterator it = channel->operators.begin();
	for (; it != channel->operators.end(); ++it)
	{
		if (*it == this)
			return true;
	}
	return false;
}

bool	User::isChannelMember(Channel *channel)
{
	std::vector<User *>::iterator it = channel->members.begin();
	for (; it != channel->members.end(); ++it)
	{
		if (*it == this)
			return true;
	}
	return false;
}

void	User::leaveChannel(Channel *toLeave)
{
	std::vector<Channel *>::iterator it = channels.begin();
	for (; it != channels.end(); ++it)
	{
		if (*it == toLeave)
		{
			channels.erase(it);
			break ;
		}
	}
}