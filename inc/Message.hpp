/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:29:09 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/03 17:48:30 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include "irc.h"

class Message
{
	public:
		Message();
		Message( int fd );
		~Message();

		std::string getCommand() const;
		std::string getParameters() const;
		void 		setCommand(std::string command);
		void 		setParameters(std::string parameters);
		

	private:
		int				_sender;
		// int				_receiver;
		std::string 	_content;
		std::string		_command;
		std::string		_parameters;
};

#endif
