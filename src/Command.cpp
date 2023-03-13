/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:57:18 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/13 12:04:50 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	helloWorld(void) 
{
	std::cout << "Hello world!" << std::endl;
}

Command::Command(void) 
{
   	_cmd.insert(std::make_pair("HELLOW", &helloWorld));
}

Command::~Command(void) 
{

}

void Command::execute(User *user)
{
    if (_cmd.find(user->getMessage()->getCommand()) != _cmd.end())
    {
        std::cout << "[SERVER]: found command!" << std::endl;
        _cmd[user->getMessage()->getCommand()]();
    }
    else
        std::cout << "[SERVER]: command not found!" << std::endl;
}