/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:34:41 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/03 15:00:23 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include "irc.h"
# include "Message.hpp"

class User
{
	public:
		Message		message;
		
		User( int fd, const char *address );
		~User();
		
		std::string getUsername() const;
		std::string getNickname() const;
		void setUsername(std::string username);
		void setNickname (std::string nickname);
		
	private:
		int			_fd;
		bool		_valid;
		const char	*_address;
		std::string _username;
		std::string _nickname;
		
		User();
};

#endif
