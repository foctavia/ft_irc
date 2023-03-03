/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:34:41 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/02 15:40:28 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include "irc.h"

class User
{
	public:
		User();
		~User();
		
		std::string getUsername() const;
		std::string getNickname() const;
		void setUsername(std::string username);
		void setNickname (std::string nickname);
		
	private:
		std::string _username;
		std::string _nickname;
};

#endif
