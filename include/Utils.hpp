/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:54:08 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/16 10:54:08 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <algorithm>
# include <sys/socket.h>
# include <unistd.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <fcntl.h>
# include <poll.h>
# include <vector>
# include <map>
# include <stdlib.h>
# include <set>
# include <sstream>
# include <ctime>

std::string					getCurrentDate();
void						sendMessage(int fd, std::string msg);
std::string					trim(const std::string& str);
std::vector<std::string>	split(const std::string& str, char delimiter);

#endif