/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:34:41 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/03 15:56:57 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include "irc.h"
# include "Message.hpp"

class User
{
	public:
		
		User( struct pollfd pfd, const char *address );
		~User();
		
		std::string getUsername() const;
		std::string getNickname() const;
		Message getMessage() const;
		struct pollfd getPollFd() const;
		int getFd() const;
		
		void setUsername(std::string username);
		void setNickname (std::string nickname);
		void setMessage(Message message);
		void setPollFd(struct pollfd pfd);
		
	private:
		bool			_valid;
		const char		*_address;
		std::string 	_username;
		std::string 	_nickname;
		Message			_message;
		struct pollfd	_pfd;
		
		User();
};

#endif
