/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:57:18 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/15 15:46:48 by sbeylot          ###   ########.fr       */
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


}

Command::~Command(void) 
{

}

std::string					Command::getName(void) const
{
	return _name;
}

std::vector<std::string>	Command::getParameters(void) const
{
	return _parameters;
}

void						Command::setName(std::string name)
{
	_name = name;
}

void						Command::setParameters(std::vector<std::string> parameters)
{
	_parameters = parameters;
}

// std::map<std::string, callCommand>	Command::getAvailableCommands(void) const
// {
// 	return _availableCommands;
// }
