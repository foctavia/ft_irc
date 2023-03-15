/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:06:08 by sbeylot           #+#    #+#             */
/*   Updated: 2023/03/15 12:12:45 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

std::vector<std::string> split(std::string str, std::string delimiter)
{
    std::vector<std::string>	values;
    std::string					value;

    size_t pos = 0;
    while ((pos = str.find(delimiter)) != std::string::npos)
    {
        value = str.substr(0, pos);
		str.erase(0, pos + delimiter.length());
		values.push_back(value);
    }
	values.push_back(str);
	return values;	
}
