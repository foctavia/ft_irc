/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 10:50:30 by foctavia          #+#    #+#             */
/*   Updated: 2023/03/24 11:37:23 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Bot.hpp"

int main(int argc, char **argv)
{
	if (argc != 4)
	{
		std::cerr << "wrong number of arguments provided\nusage: ./bot <port> <password> <nick>" << std::endl;
		return EXIT_FAILURE;
	}
		
	Bot bot(argv[1], argv[2], argv[3]);
	try
	{
		bot.run();
	}
	catch(const std::exception &e)
	{
		std::cerr << "ERROR: " << e.what() << std::endl;
	}
	
	return EXIT_SUCCESS;
}
