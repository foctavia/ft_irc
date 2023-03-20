/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:16:01 by foctavia          #+#    #+#             */
/*   Updated: 2023/03/20 17:59:16 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "irc.hpp"

class User;


class Channel
{
	// enum channelMode
	// {
	// 	CREATOR,		// O
	// 	OPERATOR,		// o
	// 	VOICE,			// v
	// 	ANONYMOUS,		// a
	// 	INVITE_ONLY,	// i
	// 	MODERATED,		// m
	// 	NO_MESSAGES, 	// n
	// 	QUIET,			// q
	// 	PRIVATE,		// p
	// 	SECRET,			// s
	// 	SERVER_REOP,	// r
	// 	TOPIC,			// t
	// 	KEY,			// k
	// 	LIMIT,			// l
	// 	BAN_MASK,		// b
	// 	EXCEPTION_MASK,	// e
	// 	INVITATION_MASK	// I
	// };

	
	public:
		std::vector<User *>			members;
		std::vector<User *>			invites;
		std::vector<User *>			operators;
		std::map<char, std::string>	modes;
		
		Channel(void);
		~Channel(void);

		std::string	getName(void) const;
		std::string getKey(void) const;
		std::string getMask(void) const;
		void		setName(std::string name);
		void		setKey(std::string key);
		void		setMask(std::string mask);

		void		sendAll(User *user, std::string message);
		bool		isMember(User *user);
	
	private:
		std::string	_name;
		std::string	_key; // password
		std::string	_mask; // password
		
		
};

#endif
