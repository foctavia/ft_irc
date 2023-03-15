/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:34:41 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/15 12:41:20 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include "irc.h"

// USER STATUS
enum status
{
	STATUS_NEW,
	STATUS_PASS,
	STATUS_NICK,
	STATUS_USER,
	STATUS_VALID
};

class Message;
class Server;
class Command;

class User
{
	public:
		std::string		input;
		
		User( struct pollfd pfd, const char *address, Server *server);
		~User();
		
		std::string 	getUsername(void) const;
		std::string		getNickname(void) const;
		struct pollfd 	getPollFd(void) const;
		int 			getFd(void) const;
		Server*			getServer(void) const;
		Command*		getCommand(void) const;
		int				getStatus(void) const;
		std::string		getHostname(void) const;
		std::string		getServername(void) const;
		std::string		getRealname(void) const;
		void			setStatus(int status);
		void			setHostname(std::string hostname);
		void			setServername(std::string servername);
		void			setRealname(std::string realname);
		void 			setUsername(std::string username);
		void 			setNickname (std::string nickname);
		
		std::string		updatedId(void);
		void 			buildMessage(void);
		void 			parseMessage(std::string input);
		void 			setPollFd(struct pollfd pfd);
		void			sendMessage(std::string message);
		std::string		formattedMessage(std::string command, std::string argument, int option);
		
	private:
		const char		*_address;
		std::string 	_username;
		std::string 	_nickname;
		std::string 	_realname;
		std::string 	_hostname;
		std::string		_servername;
		
		struct pollfd	_pfd;
		// Message*		_message;
		Command*		_command;
		Server*			_server;
		int				_status;
		
		
		User();
};

#endif
