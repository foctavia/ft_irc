/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:57:18 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/14 13:24:43 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	helloWorld(User *user) 
{
	(void)user;
	std::cout << "Hello world!" << std::endl;
}

std::string ERR_ERRONEUSNICKNAME(std::string nickname)
{
	return nickname + " :Erroneus nickname";
}

std::string	ERR_NONICKNAMEGIVEN(void)
{
	return ":No nickname given";
}

std::string	CORRECT_NICK(std::string nickname)
{
	return ": NICK :" + nickname;
}

void	nick(User *user)
{
	std::cout << "\033[1;32minside NICK\033[0m;" << std::endl;

	size_t pos = 0;
	std::string nickname = user->getMessage()->getParameters();	
	if ((pos = nickname.find(" ")) != std::string::npos)
		nickname.substr(0, pos);

	if (nickname.empty())
	{
		std::cout << ERR_NONICKNAMEGIVEN() << std::endl;
		return ;
	}
		
	std::string special_characters("[]\\`_^{|}");
	if (!isalpha(nickname[0])
		&& (special_characters.find(nickname[0]) == std::string::npos))
	{
		std::cout << ERR_ERRONEUSNICKNAME(nickname) << std::endl;
		return ;
	}
	
	if (nickname.length() > 9)
	{
		std::cout << ERR_ERRONEUSNICKNAME(nickname) << std::endl;
		return ;
	}
		
	for (std::string::iterator it = nickname.begin() + 1; it != nickname.end(); ++it)
	{
		if (!isalpha(*it)
			&& !isdigit(*it)
			&& (special_characters.find(*it) == std::string::npos)
			&& *it != '-')
		{
			std::cout << ERR_ERRONEUSNICKNAME(nickname) << std::endl;
			return ;
		}
	}	
	
	user->setNickname(nickname);
	std::cout << CORRECT_NICK(nickname) << std::endl;

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
		std::cout << user->formattedMessage(user->getMessage()->getCommand(), user->getMessage()->getParameters()) << std::endl;
    }
    else
        std::cout << "[SERVER]: command " << user->getMessage()->getCommand() << " not found!" << std::endl;
}