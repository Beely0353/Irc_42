/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:10:11 by mgayout           #+#    #+#             */
/*   Updated: 2024/09/27 14:10:11 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

/*std::string	currentDateTime()
{
	time_t		now = time(0);
	struct tm	timestruct;
	char		*buffer[1024];
	timestruct = *localtime(&now);

	strftime(buffer, sizeof(buffer), "%Y-%m-%d.%X", &timestruct);

	return buffer;
}*/

void	sendMessage(int fd, std::string msg)
{
	if (send(fd, msg.c_str(), msg.size(), 0) == -1)
		return ;
}

std::string trim(const std::string& str) {
    size_t start = 0;
    size_t end = str.length();

    while (start < end && std::isspace(static_cast<unsigned char>(str[start]))) {
        ++start;
    }

    while (end > start && std::isspace(static_cast<unsigned char>(str[end - 1]))) {
        --end;
    }

    return str.substr(start, end - start);
}

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream ss(str);

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(trim(token));
    }

    return tokens;
}
