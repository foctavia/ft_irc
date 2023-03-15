/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:51:40 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/15 12:30:51 by sbeylot          ###   ########.fr       */
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

		std::string					getName(void) const;
		std::vector<std::string>	getParameters(void) const;
		void						setName(std::string name);
		void						setParameters(std::vector<std::string> parameters);

        void    execute(User *user);
		
    private:
		std::map<std::string, callCommand>	_cmd;
		std::string							_name;
		std::vector<std::string>			_parameters;

};

#endif
