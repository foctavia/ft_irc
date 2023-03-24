/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 10:24:15 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/24 11:40:19 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
# define BOT_HPP

# include "irc.hpp"

class Bot
{
	typedef void(*callCommand)(User *user);

	public:
		Bot(void);
		~Bot();

		void	TIME(void);
		void	HELP(void);
	
	private:
		std::string _name;
		std::map<std::string, callCommand> _commands;
		Server*				_server;
};

#endif