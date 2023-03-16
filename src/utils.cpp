/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:06:08 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/16 19:05:08 by foctavia         ###   ########.fr       */
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

void	displayActivity(User *user, std::string arg, int option)
{
	const std::time_t	current = std::time(NULL);
	
	std::cout << "[" << std::asctime(std::localtime(&current)) << "\b][SERVER]:";
	
	if (option != NONE)
	{
		if (option == SEND)
			std::cout << " receive " << arg << " from ";
		else
			std::cout << " send " << arg << " to ";
		std::cout << "[" << user->getFd() << "]" << user->getNickname() << std::endl;
	}
	else
		std::cout << arg << std::endl;
		
}
	
template <typename T>
void	printVector(T container)
{
	for (typename T::iterator it = container.begin(); it != container.end(); ++it)
		std::cout << " " << *it;
	std::cout << std::endl;
}
