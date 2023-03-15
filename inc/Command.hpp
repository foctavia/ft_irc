/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:51:40 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/15 15:11:04 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP

# include "irc.hpp"

class User;

class Command
{
	typedef void(*callCommand)(User *user);

    public:
		std::map<std::string, callCommand>	availableCommands;
		
        Command();
        ~Command();

		std::string							getName(void) const;
		std::vector<std::string>			getParameters(void) const;
		// std::map<std::string, callCommand>	getAvailableCommands(void) const;
		void								setName(std::string name);
		void								setParameters(std::vector<std::string> parameters);

    private:
		std::string							_name;
		std::vector<std::string>			_parameters;

};

#endif
