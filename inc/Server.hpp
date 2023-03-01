/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:25:40 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/01 11:20:47 by foctavia         ###   ########.fr       */
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

		void	createServer( void );
		void	clean( void );

		char	*getPort( void ) const;
		char	*getPassword( void ) const;
	
	private:
		char			*_port;
		char			*_password;
	
		struct addrinfo *_serverInfo;
		int				_socketFd;
		
		Server( void );
};

#endif