/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:29:09 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/03 14:59:18 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include "irc.h"

class Message
{
	public:
	
		Message() { }
		~Message() { }

	private:
		// int				_sender;
		// int				_receiver;
		std::string 	_content;
		std::string		_buffer;
		std::string		_command;
};

#endif
