/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:25:15 by owalsh            #+#    #+#             */
/*   Updated: 2023/03/13 15:18:43 by foctavia         ###   ########.fr       */
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

#endif