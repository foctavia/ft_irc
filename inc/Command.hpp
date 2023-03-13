/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:51:40 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/13 15:10:31 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP

# include "irc.h"

class User;

class Command
{
	typedef void(*callCommand)(User *user);

    public:
        Command();
        ~Command();

        void execute(User *user);
		
    private:
		std::map<std::string, callCommand> _cmd;

};

#endif