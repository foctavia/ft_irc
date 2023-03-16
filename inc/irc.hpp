/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:25:15 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/15 15:10:11 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
# define IRC_HPP

# include <stdlib.h>
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
# include <numeric>
# include <sys/time.h>
# include <ctime>

# include "defines.h"

# include "Server.hpp"
# include "User.hpp"
# include "Command.hpp"

void						displayActivity(User *user, std::string arg, int option);
void						*getIpAddress(struct sockaddr *socketAddress);
std::vector<std::string>	split(std::string str, std::string delimiter);
std::string					accumulate(std::vector<std::string> vec, std::string delimiter, int pos);


void	USER(User *user);
void	PASS(User *user);
void	NICK(User *user);
void	PRIVMSG(User *user);
void	QUIT(User *user);
void	PING(User *user);
void	PONG(User *user);

std::string ERR_UNKNOWNCOMMAND(std::string command);
std::string ERR_ERRONEUSNICKNAME(std::string nickname);
std::string	ERR_NONICKNAMEGIVEN(void);
std::string	ERR_NEEDMOREPARAMS(std::string command);
std::string	ERR_ALREADYREGISTRED(void);
std::string	ERR_NOSUCHNICK(std::string name);
std::string	ERR_NOORIGIN(std::string name);

std::string RPL_WELCOME(User *user);

#endif