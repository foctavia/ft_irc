/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:51:40 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/16 17:36:02 by foctavia         ###   ########.fr       */
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
		
        Command(void);
        ~Command(void);

		std::string					getName(void) const;
		std::vector<std::string>	getParameters(void) const;
		void						setName(std::string name);
		void						setParameters(std::vector<std::string> parameters);

    private:
		std::string					_name;
		std::vector<std::string>	_parameters;
};

#endif
