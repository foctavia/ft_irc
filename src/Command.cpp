/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:57:18 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/13 18:29:42 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	helloWorld(User *user) 
{
	(void)user;
	std::cout << "Hello world!" << std::endl;
}

void	nick(User *user)
{
	std::cout << "\033[1;32minside NICK\033[0m;" << std::endl;

	size_t pos = 0;
	std::string param = user->getMessage()->getParameters();	
	if ((pos = param.find(" ")) != std::string::npos)
		param.substr(0, pos);
	user->setNickname(param);

	if (user->getStatus() == STATUS_PASS)
		user->setStatus(STATUS_NICK);
	else if (user->getStatus() == STATUS_USER)
		user->setStatus(STATUS_VALID);
}

void	user(User *user)
{
	std::cout << "\033[1;32minside USER\033[0m;" << std::endl;

	size_t pos = 0;
	std::string param = user->getMessage()->getParameters();
	
	if ((pos = param.find(" ")) != std::string::npos)
		param.substr(0, pos);
	user->setUsername(param);
	
	if (user->getStatus() == STATUS_PASS)
		user->setStatus(STATUS_USER);
	else if (user->getStatus() == STATUS_NICK)
		user->setStatus(STATUS_VALID);
}

void	pass(User *user)
{
	std::cout << "\033[1;32minside PASS\033[0m;" << std::endl;

	size_t pos = 0;
	std::string param = user->getMessage()->getParameters();
	
	if ((pos = param.find(" ")) != std::string::npos)
		param.substr(0, pos);
	if (param == user->getServer()->getPassword())
	{
		std::cout << "\033[1;32mPassword is correct\033[0m;" << std::endl;
		if (user->getStatus() == STATUS_NEW)
			user->setStatus(STATUS_PASS);
	}	
}

void	quit(User *user)
{
	std::cout << "\033[1;32minside QUIT\033[0m;" << std::endl;
	if (send(user->getFd(), "\n", 2, MSG_NOSIGNAL) == -1)
		perror("send");
	user->getServer()->disconnect(user->getPollFd());
}

Command::Command(void) 
{
   	_cmd.insert(std::make_pair("HELLOW", &helloWorld));
   	_cmd.insert(std::make_pair("NICK", &nick));
   	_cmd.insert(std::make_pair("PASS", &pass));
   	_cmd.insert(std::make_pair("USER", &user));
   	_cmd.insert(std::make_pair("QUIT", &quit));

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
    }
    else
        std::cout << "[SERVER]: command " << user->getMessage()->getCommand() << " not found!" << std::endl;
}