/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:24:28 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/01 14:24:13 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.h"
# include "Server.hpp"

int main(int argc, char **argv)
{
	if (argc != 3)
		return ft_error(ERR_ARGC);
		
	Server server(argv[1], argv[2]);

	try
	{
		server.createSocket();
	}
	catch(const std::exception &e)
	{
		std::cerr << "ERROR: " << e.what() << std::endl;
	}
	
	return 0;
}
