/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 10:58:17 by foctavia          #+#    #+#             */
/*   Updated: 2023/03/24 15:39:40 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

void	HELP(Bot *bot)
{
	std::vector<std::string> messages;
	
	
	messages.push_back("PRIVMSG " + bot->dest + " :List of available commands:\r\n");
	messages.push_back("PRIVMSG " + bot->dest + " :TIME: display current time\r\n");
	messages.push_back("PRIVMSG " + bot->dest + " :INTRODUCE: short introduction of Felicia the bot\r\n");
	messages.push_back("PRIVMSG " + bot->dest + " :JOIN #bot: you won't regret it\r\n");

	for (std::vector<std::string>::iterator it = messages.begin(); it != messages.end(); ++it)
	{
		if (send(bot->socketFd, (*it).c_str(), (*it).length(), MSG_NOSIGNAL) == -1)
			perror("send");
	}
}

void	TIME(Bot *bot)
{
	std::time_t	now = std::time(0);
	std::string currentTime = ctime(&now);
	
	std::string message;
	message += "PRIVMSG " + bot->dest + " :";
	message += "Currently it is " + currentTime + "\r\n";
	if (send(bot->socketFd, message.c_str(), message.length(), MSG_NOSIGNAL) == -1)
		perror("send");
}

void	INTRODUCE(Bot *bot)
{
	std::vector<std::string> messages;
	
	messages.push_back("PRIVMSG " + bot->dest + " :Hello, I'm Felicia the BOT\r\n");
	messages.push_back("PRIVMSG " + bot->dest + " :I've been created by 3 beautiful people sitting next to you\r\n");
	messages.push_back("PRIVMSG " + bot->dest + " :Hope you like their project and give them a perfect score\r\n");
	messages.push_back("PRIVMSG " + bot->dest + " :Just saying, it's an outstanding project\r\n");
	messages.push_back("PRIVMSG " + bot->dest + " :Bye\r\n");
	for (std::vector<std::string>::iterator it = messages.begin(); it != messages.end(); ++it)
	{
		if (send(bot->socketFd, (*it).c_str(), (*it).length(), MSG_NOSIGNAL) == -1)
			perror("send");
	}	
}


Bot::Bot(char *port, char *password, char *nick)
	: _port(port), _password(password), _nick(nick)
{
	gettimeofday(&_start, NULL);
	
	_command.insert(std::make_pair("HELP", &HELP));
	_command.insert(std::make_pair("TIME", &TIME));
	_command.insert(std::make_pair("INTRODUCE", &INTRODUCE));

	jokes.push_back("Why is it always hot in the corner of a room? Because a corner is 90 degrees.");
	jokes.push_back("I'm reading a book about anti-gravity. I can't put it down.");
	jokes.push_back("Once you've seen one shopping center, you've seen the mall.");
	jokes.push_back("I was wondering why the baseball was getting bigger. Then it hit me.");
	jokes.push_back("I'm thinking of reasons to go to Switzerland. The flag is a big plus.");
	jokes.push_back("Why can't you play poker on the African Savanna? There's too many cheetahs.");
	jokes.push_back("Why can't a bicycle stand on its own? It's two-tired.");
}

Bot::~Bot(void)
{
	close(socketFd);
}


int	Bot::getListenerSocket(void)
{
	int				listenerFd = -1;
	int 			status = 0;
	struct addrinfo hints, *tmp;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	status = getaddrinfo("127.0.0.1", _port, &hints, &_serverInfo);
	if (status != 0)
		throw std::runtime_error("getaddrinfo()");

	for (tmp = _serverInfo; tmp != NULL; tmp = tmp->ai_next)
	{
		listenerFd = socket(tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol);
		if (listenerFd < 0)
			continue ;
			
		if (connect(listenerFd, tmp->ai_addr, tmp->ai_addrlen) == -1)
		{
			close(listenerFd);
			listenerFd = -1;
			continue ;
		}
		
		break ;
	}

	if (tmp == NULL)
		throw std::runtime_error("failed to connect bot");
		
	freeaddrinfo(_serverInfo);
	_serverInfo = NULL;

	return listenerFd;
}

void	Bot::connection(void)
{
	std::string connect;
	
	connect += "PASS " + _password + "\r\n";
	connect += "NICK " + _nick + "\r\n";
	connect += "USER bot bot localhost :bot\r\n";
	if (send(socketFd, connect.c_str(), connect.length(), MSG_NOSIGNAL) == -1)
		perror("send");
	
	connect = "JOIN #bot\r\n";
	if (send(socketFd, connect.c_str(), connect.length(), MSG_NOSIGNAL) == -1)
		perror("send");
}


void	Bot::parseMessage(std::string buffer)
{
	std::string command;
	
	if (buffer.find("PRIVMSG") != std::string::npos)
	{
		size_t pos = buffer.find("!");
		
		dest = buffer.substr(1, pos - 1);
		
		buffer.erase(0, pos);
		pos = buffer.find(":");
		command = buffer.substr(pos + 1, buffer.length());
		pos = command.find("\r\n");
		command.erase(pos);
		
		if (_command.find(command) != _command.end())
			_command[command](this);
	}
	else if (buffer.find("JOIN :#bot") != std::string::npos)
	{
		size_t pos = buffer.find("!");
		dest = buffer.substr(1, pos - 1);
		
		if (dest != _nick)
			_users.push_back(dest);
	}
	else if (buffer.find("PING") != std::string::npos)
	{
		std::string message;
		message = "PONG " + _nick + "\r\n";
		if (send(socketFd, message.c_str(), message.length(), MSG_NOSIGNAL) == -1)
			perror("send");
	}
	
}

void	Bot::floodUser(void)
{
	std::vector<std::string>::iterator it = _users.begin();
	struct timeval	current;
	
	gettimeofday(&current, NULL);
	for (; it != _users.end(); ++it)
	{
		long	lastPing = (current.tv_sec - _start.tv_sec);
		if (lastPing >= 5)
		{
			std::string message = "PRIVMSG " + *it + " :";
			int random = std::rand() % jokes.size();
			std::string joke = jokes[random];
			message += joke + "\r\n";
			if (send(socketFd, message.c_str(), message.length(), MSG_NOSIGNAL) == -1)
				perror("send");
		}
	}
}

void	Bot::receiveMessage(void)
{
	char buffer[512];
	memset(buffer, 0, sizeof buffer);

	int nbytes;
	while ((nbytes = recv(socketFd, buffer, sizeof buffer, 0)) != 0)
	{
		if (!_users.empty())
			floodUser();
		if (nbytes == -1)
			throw std::runtime_error("recv()");
		else if (nbytes)
			parseMessage(buffer);
		memset(buffer, 0, sizeof buffer);
	}

}


void	Bot::run(void)
{
	try
	{
		socketFd = getListenerSocket();
	}
	catch(const std::exception& e)
	{
		std::cerr << "ERROR: " << e.what() << std::endl;
		return ;
	}
	
	connection();
	receiveMessage();
	
}