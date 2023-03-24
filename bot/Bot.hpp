/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 10:52:14 by foctavia          #+#    #+#             */
/*   Updated: 2023/03/24 15:26:14 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
# define BOT_HPP

# include <stdlib.h>
# include <iostream>
# include <string>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <cstdio>
# include <cstring>
# include <errno.h>
# include <stdexcept>
# include <vector>
# include <map>
# include <poll.h>
# include <unistd.h>
# include <arpa/inet.h>
# include <iomanip>
# include <utility>
# include <numeric>
# include <sys/time.h>
# include <ctime>
# include <string> 
# include <sstream>

class Bot
{
	public:
		typedef void(*callCommand)(Bot *bot);

		int									socketFd;
		std::string							dest;
		std::vector<std::string>			jokes;
		
		Bot(char *port, char *password, char *nick);
		~Bot(void);

		int		getListenerSocket(void);
		void	run(void);
		void	connection(void);
		void	receiveMessage(void);
		void	parseMessage(std::string buffer);
		void	floodUser(void);



	private:
	
		char		*_port;
		std::string	_password;
		std::string	_nick;
		
		struct timeval	_start;

		struct addrinfo						*_serverInfo;
		std::map<std::string, callCommand>	_command;
		std::vector<std::string>			_users;

		Bot(void);
};

// void	HELP();
#endif