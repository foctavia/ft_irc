/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 10:25:52 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/24 11:38:35 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Bot.hpp"

Bot::Bot(void)
	_name("Felicia")
{
		
}

Bot::~Bot()
{

}


Bot::TIME(std::string message)
{
	std::time_t	now = std::time(0);
	std::string currentTime = ctime(&now);
	std::cout << "Current time: " << currentTime << std::endl;
}

void	Bot::receiveMessage(struct pollfd pfd)
{
	// User *user;
	
	// std::map<int, User *>::iterator it = _users.find(pfd.fd);
	// if (it == _users.end())
	// 	user = NULL;
	// else 
	// 	user = (*it).second;
	
	char buffer[512];
	memset(buffer, 0, sizeof buffer);

	int nbytes = recv(pfd.fd, buffer, sizeof buffer, 0);

	// if (user != NULL && nbytes == 0)
		// disconnect(user);
	if (nbytes < 0)
		throw std::runtime_error("recv()");
	
	user->input.append(buffer);
	size_t pos = 0;

	user->parseMessage(cmd);
	user->execute();

	if (user != NULL && !user->input.empty())
		user->input = "";
}