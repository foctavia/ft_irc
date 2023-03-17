/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:22:54 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/14 11:19:13 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map>
#include <iostream>

typedef void(*RPL)(std::string arg);
/* Client Server connections */
//	001
std::string RPL_WELCOME(std::string user);

//	002
std::string RPL_YOURHOST(std::string servername);

int main(void) {

	std::map<int, RPL> rpl;

	rpl.insert(std::make_pair(001, &RPL_WELCOME));
		
	return (0);
}

