/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:25:15 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/15 11:46:20 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_H
# define IRC_H

# include "defines.h"

# include <iostream>
# include <string>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <cstdio>
# include <cstring>
# include <errno.h>
# include <stdexcept>
# include <vector>
# include <map>
# include <poll.h>
# include <unistd.h>
# include <arpa/inet.h>
# include <iomanip>
# include <utility>

# include "Server.hpp"
# include "User.hpp"
# include "Message.hpp"
# include "Command.hpp"

int ft_error(int type);
void	USER(User *user);
void	PASS(User *user);
void	NICK(User *user);
void	QUIT(User *user);

std::string ERR_UNKNOWNCOMMAND(std::string command);
std::string ERR_ERRONEUSNICKNAME(std::string nickname);
std::string	ERR_NONICKNAMEGIVEN(void);
std::string	ERR_NEEDMOREPARAMS(std::string command);
std::string	ERR_ALREADYREGISTRED(void);


std::string RPL_WELCOME(User *user);

#endif