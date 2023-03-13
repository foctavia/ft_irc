/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:25:40 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/13 12:01:17 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "irc.h"

class Server
{
	public:
		Server( char *port, char *password );
		~Server( void );

		int		getListenerSocket( void );
		void	addSocket( int newFd );
		void	run( void );
		void	newConnection( void );
		void	receiveMessage( struct pollfd pfd );
		void	sendMessage( int senderFd, std::string &message );
		void	disconnect( struct pollfd pfd );
		void	clean( void );


		char	*getPort( void ) const;
		char	*getPassword( void ) const;
	
	private:
		char				*_port;
		char				*_password;
	
		struct addrinfo 	*_socketInfo;
		int					_socketFd;

		std::vector<struct pollfd>	_pollFds;
		std::map<int, User *>		_users;
		// std::map<std::string, CallCmd> _cmd;
		Command*	_cmd;
		
		Server( void );
};

#endif