/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:57:18 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/23 16:14:07 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

Command::Command(void) 
{
   	availableCommands.insert(std::make_pair("NICK", &NICK));
   	availableCommands.insert(std::make_pair("PASS", &PASS));
   	availableCommands.insert(std::make_pair("USER", &USER));
   	availableCommands.insert(std::make_pair("PRIVMSG", &PRIVMSG));
   	availableCommands.insert(std::make_pair("QUIT", &QUIT));
   	availableCommands.insert(std::make_pair("PING", &PING));
   	availableCommands.insert(std::make_pair("PONG", &PONG));
   	availableCommands.insert(std::make_pair("KILL", &KILL));
   	availableCommands.insert(std::make_pair("OPER", &OPER));
   	availableCommands.insert(std::make_pair("JOIN", &JOIN));
   	availableCommands.insert(std::make_pair("MODE", &MODE));
   	availableCommands.insert(std::make_pair("NAMES", &NAMES));
   	availableCommands.insert(std::make_pair("TOPIC", &TOPIC));
   	availableCommands.insert(std::make_pair("INVITE", &INVITE));
   	availableCommands.insert(std::make_pair("LIST", &LIST));
   	availableCommands.insert(std::make_pair("PART", &PART));
   	availableCommands.insert(std::make_pair("KICK", &KICK));
   	availableCommands.insert(std::make_pair("INFO", &INFO));
   	availableCommands.insert(std::make_pair("info", &INFO));
   	availableCommands.insert(std::make_pair("TIME", &TIME));
   	availableCommands.insert(std::make_pair("time", &TIME));
   	availableCommands.insert(std::make_pair("VERSION", &VERSION));
   	availableCommands.insert(std::make_pair("version", &VERSION));
   	availableCommands.insert(std::make_pair("NOTICE", &NOTICE));
   	availableCommands.insert(std::make_pair("DIE", &DIE));
   	availableCommands.insert(std::make_pair("die", &DIE));


}

Command::~Command(void) 
{
	
}

std::string	Command::getName(void) const
{
	return _name;
}

std::vector<std::string>	Command::getParameters(void) const
{
	return _parameters;
}

void	Command::setName(std::string name)
{
	_name = name;
}

void	Command::setParameters(std::vector<std::string> parameters)
{
	_parameters = parameters;
}

void Command::clear(void)
{
	clearName();
	clearParameters();
}

void Command::clearParameters(void)
{
	_parameters.clear();
}

void Command::clearName(void)
{
	_name.clear();
}