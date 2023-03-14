/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:57:18 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/14 17:00:35 by sbeylot          ###   ########.fr       */
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

void	Command::execute(User *user)
{
    if (_cmd.find(user->getMessage()->getCommand()) != _cmd.end())
    {
        std::cout << "[SERVER]: found command!" << std::endl;
        _cmd[user->getMessage()->getCommand()](user);
		std::cout << user->formattedMessage(user->getMessage()->getCommand(), user->getMessage()->getParameters()) << std::endl;
    }
    else
        std::cout << "[SERVER]: command " << user->getMessage()->getCommand() << " not found!" << std::endl;
}