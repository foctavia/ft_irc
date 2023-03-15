/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:57:18 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/15 12:40:05 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

Command::Command(void) 
{
   	_cmd.insert(std::make_pair("NICK", &NICK));
   	_cmd.insert(std::make_pair("PASS", &PASS));
   	_cmd.insert(std::make_pair("USER", &USER));
   	_cmd.insert(std::make_pair("QUIT", &QUIT));

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

void	Command::execute(User *user)
{
    if (_cmd.find(user->getCommand()->getName()) != _cmd.end())
    {
        std::cout << "[SERVER]: found command!" << std::endl;
        _cmd[user->getCommand()->getName()](user);
		// std::cout << user->formattedMessage(user->getMessage()->getCommand(), user->getMessage()->getParameters()) << std::endl;
    }
    else
        std::cout << "[SERVER]: command " << user->getCommand()->getName() << " not found!" << std::endl;
}