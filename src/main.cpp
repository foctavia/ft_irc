/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:24:28 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/23 15:18:48 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"
# include "Server.hpp"
# include <csignal>

bool g_running = true;

void	handler(int signum)
{
	if (signum == SIGINT)
	{
		g_running = false;		
	}
}

int main(int argc, char **argv)
{
	signal(SIGINT, handler);
	if (argc != 3)
	{
		std::cerr << "wrong number of arguments provided\nusage: ./ircserv <port> <password>" << std::endl;
		return EXIT_FAILURE;
	}
		
	Server server(argv[1], argv[2]);
	try
	{
		server.run();
	}
	catch(const std::exception &e)
	{
		std::cerr << "ERROR: " << e.what() << std::endl;
	}
	
	return EXIT_SUCCESS;
}
