/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:34:41 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/14 13:18:57 by owalsh           ###   ########.fr       */
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

class User
{
	public:
		std::string		input;
		
		User( struct pollfd pfd, const char *address, Server *server);
		~User();
		
		std::string 	getUsername() const;
		std::string		getNickname() const;
		struct pollfd 	getPollFd() const;
		int 			getFd() const;
		Server*			getServer() const;
		
		void 			setUsername(std::string username);
		void 			setNickname (std::string nickname);
		void 			setPollFd(struct pollfd pfd);
		void 			buildMessage();
		Message*		getMessage() const;
		int				getStatus() const;
		void			setStatus(int status);

		void			sendMessage(std::string message);


		void 			parseMessage();
		std::string		formattedMessage(std::string command, std::string argument);
		
	private:
		const char		*_address;
		std::string 	_username;
		std::string 	_nickname;
		struct pollfd	_pfd;
		Message*		_message;
		Server*			_server;
		int				_status;
		
		
		User();
};

#endif
