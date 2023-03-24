/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 10:52:14 by foctavia          #+#    #+#             */
/*   Updated: 2023/03/24 11:22:10 by foctavia         ###   ########.fr       */
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
		Bot(char *port, char *password, char *nick);
		~Bot(void);

		int		getListenerSocket(void);
		void	run(void);

	private:
	
		char	*_port;
		char	*_password;
		char	*_nick;

		struct addrinfo	*_serverInfo;
		int				_socketFd;

		Bot(void);
};

#endif