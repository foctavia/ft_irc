/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:06:08 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/17 17:13:04 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	*getIpAddress(struct sockaddr *socketAddress)
{
	if (socketAddress->sa_family == AF_INET)
		return &(((struct sockaddr_in *)socketAddress)->sin_addr);

	return &(((struct sockaddr_in6 *)socketAddress)->sin6_addr);
}

std::vector<std::string>	split(std::string str, std::string delimiter)
{
	std::vector<std::string>	values;
	std::string					value;

	size_t pos = 0;
	while ((pos = str.find(delimiter)) != std::string::npos)
	{
		value = str.substr(0, pos);
		str.erase(0, pos + delimiter.length());
		values.push_back(value);
	}
	values.push_back(str);
	return values;	
}

std::string	accumulate(std::vector<std::string> vec, std::string delimiter, int pos)
{
	std::string str;
	
	for (std::vector<std::string>::iterator it = vec.begin() + pos; it != vec.end(); ++it)
	{
		str.append(*it);
		if (it != vec.end() - 1)
			str.append(delimiter);
	}
	return str;
}

void	displayTime(void)
{
	std::time_t	now = std::time(0);
	std::tm		*currentTime = std::localtime(&now);
	
	std::cout << "["
		<< currentTime->tm_hour << ":"
		<< currentTime->tm_min << ":";
	if (currentTime->tm_sec < 10)
		std::cout << "0";
	std::cout << currentTime->tm_sec << "] "; 
}

void	displayActivity(User *user, std::string arg, int option)
{
	displayTime();
	
	if (option != NONE)
	{
		if (option == SEND)
		{
			std::cout << ITALIC << "from " << RESET << "[SERVER] " << ITALIC << "to" << RESET " [" << user->getFd();
			if (!user->getNickname().empty())
				std::cout << " " << ITALIC << user->getNickname() << RESET;
			std::cout << "]";
		}
		else
		{
			std::cout << ITALIC << "from" << RESET << " [" << user->getFd(); 
			if (!user->getNickname().empty())
				std::cout << " " << ITALIC << user->getNickname() << RESET;
			std::cout << "] " << ITALIC << "to" RESET << " [SERVER]";
		}
		std::cout << " " << BOLD << ITALIC << arg << RESET << std::endl;
	}
	else
		std::cout << " " << arg << std::endl;
}
	
template <typename T>
void	printVector(T container)
{
	for (typename T::iterator it = container.begin(); it != container.end(); ++it)
		std::cout << " " << *it;
	std::cout << std::endl;
}
