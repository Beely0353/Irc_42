/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:18:12 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/18 19:56:40 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

std::vector<std::string>    Server::splitBuffer(std::string buf)
{
	std::vector<std::string>	command;
	std::string					tmp;

	for (unsigned int i = 0, j = 0; i != buf.size(); i++)
	{
		if (buf[i] == ' ')
		{
			tmp = buf.substr(j, i - j);
			command.push_back(tmp);
			j = i + 1;
		}
		else if (buf[i] == '\n')
		{
			tmp = buf.substr(j, i - (j + 1) );
			command.push_back(tmp);
			break;
		}
	}
	
	return command;
}

int	Server::nicknameUsed(std::string nick)
{
	for (unsigned int i = 1; i != this->_nbClient; i++)
	{
		if (this->_clients[this->_pfds[i].fd]->getNickname() == nick)
			return this->_clients[this->_pfds[i].fd]->getSocket();
	}
	return 0;
}

int	Server::usernameUsed(std::string user)
{
	for (unsigned int i = 1; i != this->_nbClient; i++)
	{
		if (this->_clients[this->_pfds[i].fd]->getUsername() == user)
			return this->_clients[this->_pfds[i].fd]->getSocket();
	}
	return 0;
}

void	Server::sendChannel(Channel *channel, std::string message)
{
	for (std::map<std::string, bool>::iterator it = channel->getMembers().begin(); it != channel->getMembers().end(); ++it)
		for (unsigned int i = 1; i < this->getNbClient(); i++)
			if (this->_clients[this->_pfds[i].fd]->getUsername() == it->first)
				send(this->_clients[this->_pfds[i].fd]->getSocket(), message.c_str(), message.size(), 0);
}