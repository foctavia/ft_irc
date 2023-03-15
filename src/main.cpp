/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:24:28 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/15 15:11:04 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"
# include "Server.hpp"

int main(int argc, char **argv)
{
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
