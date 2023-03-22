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
# include <string> 
# include <sstream>

# include "defines.h"

# include "Server.hpp"
# include "User.hpp"
# include "Command.hpp"
# include "Channel.hpp"

void						displayActivity(User *user, std::string arg, int option);
void						displayTime(void);
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
void	KILL(User *user);
void	OPER(User *user);
void	JOIN(User *user);
void	MODE(User *user);
void	LIST(User *user);
void	NAMES(User *user);
void	PART(User *user);
void	LIST(User *user);
void	TOPIC(User *user);
void	INVITE(User *user);
void	KICK(User *user);
void	INFO(User *user);
void	STAT(User *user);
void	TIME(User *user);
void	VERSION(User *user);

std::string ERR_UNKNOWNCOMMAND(std::string command);
std::string ERR_ERRONEUSNICKNAME(std::string nickname);
std::string	ERR_NONICKNAMEGIVEN(void);
std::string	ERR_NEEDMOREPARAMS(std::string command);
std::string	ERR_ALREADYREGISTRED(void);
std::string	ERR_NOSUCHNICK(std::string name);
std::string	ERR_NOORIGIN(std::string name);
std::string ERR_NOPRIVILEGES(std::string name);
std::string	ERR_PASSWDMISMATCH(void);
std::string	ERR_NOOPERHOST(void);
std::string	ERR_NICKNAMEINUSE(std::string nickname);
std::string	ERR_BADCHANMASK(std::string channel);
std::string	ERR_BADCHANNELKEY(std::string channel);
std::string	ERR_USERSDONTMATCH(void);
std::string ERR_UMODEUNKNOWNFLAG(void);
std::string	ERR_NOSUCHCHANNEL(std::string channel);
std::string ERR_UNKNOWNMODE(char c, std::string channel);
std::string	ERR_NOTONCHANNEL(std::string channel);
std::string ERR_CHANOPRIVSNEEDED(std::string channel);
std::string	ERR_USERNOTINCHANNEL(std::string nick, std::string channel);
std::string	ERR_USERONCHANNEL(std::string nick, std::string channel);


std::string RPL_WELCOME(User *user);
std::string RPL_YOUREOPER();
std::string RPL_YOURHOST(void);
std::string RPL_CREATED(User *user); 
std::string RPL_MYINFO(void);
std::string RPL_UMODEIS(User *user);
std::string RPL_CHANNELMODEIS(Channel *channel);
std::string RPL_NAMREPLY(Channel *channel);
std::string RPL_ENDOFNAMES(std::string channel);
std::string RPL_TOPIC(Channel *channel);
std::string RPL_NOTOPIC(std::string channel);
std::string RPL_LIST(Channel *channel);
std::string RPL_LISTEND(void);
std::string RPL_INVITING(std::string channel, std::string nick);
std::string RPL_INFO(std::string string);
std::string RPL_ENDOFINFO(void);
std::string RPL_TIME(void);
std::string RPL_VERSION(void);

#endif