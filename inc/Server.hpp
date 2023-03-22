/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:25:40 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/22 14:34:44 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "irc.hpp"

class User;
class Command;
class Channel;

class Server
{
	public:
		std::vector<Channel *>	channels;
		
		Server(char *port, char *password);
		~Server(void);

		int			getListenerSocket(void);
		void		addSocket(int newFd);
		void		run(void);
		void		newConnection(void);
		void		receiveMessage(struct pollfd pfd);
		void		disconnect(User* user);
		void		clean(void);
		void		checkConnection(void);
		User*		findUserNickname(std::string nickname);
		Channel*	findChannel(std::string name);
		
		void		eraseChannel(Channel *channel);
		


		char					*getPort(void) const;
		char					*getPassword(void) const;
		std::map<int, User *>	getUsers(void) const;
		char*					getStartingTime(void) const;	
			
	private:
		char						*_port;
		char						*_password;
	
		struct addrinfo 			*_socketInfo;
		struct timeval				_start;
		char*						_startingTime;
		int							_socketFd;

		std::vector<struct pollfd>	_pollFds;
		std::map<int, User *>		_users;
		Command*					_cmd;

		Server(void);
};

#endif