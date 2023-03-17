/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:06:08 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/17 10:33:49 by foctavia         ###   ########.fr       */
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
	
	std::cout << "[" << 1900 + currentTime->tm_year << "-"
		<< 1 + currentTime->tm_mon << "-"
		<< currentTime->tm_mday << " "
		<< currentTime->tm_hour << ":"
		<< currentTime->tm_min << ":"
		<< currentTime->tm_sec << "]"; 
}

void	displayActivity(User *user, std::string arg, int option)
{
	displayTime();
	
	std::cout << "[SERVER]:";
	
	if (option != NONE)
	{
		if (option == SEND)
			std::cout << " send " << GREEN << arg << RESET << " to ";
		else
			std::cout << " receive " << GREEN << arg << RESET << " from ";
		std::cout << "[" << user->getFd() << "." << user->getNickname() << "]" << std::endl;
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
