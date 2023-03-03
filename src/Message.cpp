/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:41:20 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/03 17:48:49 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Message.hpp"

Message::Message()
{

}

Message::Message( int fd )
	: _sender(fd)
{
	(void)_sender;
}

Message::~Message()
{
	
}


/* GETTERS AND SETTERS */ 

void Message::setCommand(std::string command)
{
	_command = command;	
}

void Message::setParameters(std::string parameters)
{
	_parameters = parameters;
}

std::string Message::getCommand() const
{
	return _command;
}

std::string Message::getParameters() const
{
	return _parameters;
}
