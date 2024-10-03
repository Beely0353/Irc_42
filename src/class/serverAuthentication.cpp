/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverAuthentication.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:22:01 by mgayout           #+#    #+#             */
/*   Updated: 2024/09/26 11:22:01 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

/*void	Server::authentication()
{	
	std::string	str, nick = "", user = "";
	char	buffer[1024] = {0};
	int		bytes_received;

	fcntl(this->_clients[this->_nbClient]->getSocket(), F_SETFL, O_NONBLOCK);
	if ((bytes_received = recv(this->_clients[this->_nbClient]->getSocket(), buffer, 1024, 0)) > 0)
	{
		buffer[bytes_received] = '\0';
		nick = this->findNickname(buffer);
		user = this->findUsername(buffer);
	}
	fcntl(this->_clients[this->_nbClient]->getSocket(), F_SETFL, 0);
	this->setNickClient(nick);
	this->setUserClient(user);
}

std::string	Server::findNickname(char *buffer)
{
	std::string	nick = "", tmp = buffer;
	size_t		start, end;

	if ((start = tmp.find("NICK")) < tmp.size())
	{
		start += 5;
		end = start;
		while (tmp[end] && tmp[end] != '\n')
			end++;
		nick = tmp.substr(start, (end - start) - 1);
	}

	return nick;
}

std::string	Server::findUsername(char *buffer)
{
	std::string	user = "", tmp = buffer;
	size_t		start, end;

	if ((start = tmp.find("USER")) < tmp.size())
	{
		start += 5;
		end = start;
		while (tmp[end] && tmp[end] != '\n')
			end++;
		user = tmp.substr(start, (end - start) - 1);
	}

	return user;
}

void	Server::setNickClient(std::string nick)
{
	char		buffer[1024] = {0};
	int			bytes_received;

	if (nick.size())
	{
		send(this->_clients[this->_nbClient]->getSocket(), "[Server] Would you want to keep this nickname \"", 48, 0);
		send(this->_clients[this->_nbClient]->getSocket(), nick.c_str(), nick.size(), 0);
		send(this->_clients[this->_nbClient]->getSocket(), "\" ?\n[Server] yes or no ?\n", 24, 0);
		while (1)
		{
			if ((bytes_received = recv(this->_clients[this->_nbClient]->getSocket(), buffer, 1024, 0)) > 0)
				buffer[bytes_received] = '\0';
			if (bytes_received == 5 && buffer[0] == 'y' && buffer[1] == 'e' && buffer[2] == 's')
			{
				this->_clients[this->_nbClient]->setNickname(nick);
				return ;
			}
			else if (bytes_received == 4 && buffer[0] == 'n' && buffer[1] == 'o')
				break ;
			else
				send(this->_clients[this->_nbClient]->getSocket(), "[Server] yes or no ?\n", 22, 0);
		}
	}
	send(this->_clients[this->_nbClient]->getSocket(), "[Server] Type your new nickname\n", 33, 0);
	while (1)
	{
		if ((bytes_received = recv(this->_clients[this->_nbClient]->getSocket(), buffer, 1024, 0)) > 0)
			buffer[bytes_received] = '\0';
		if (buffer[0] == '\n')
			send(this->_clients[this->_nbClient]->getSocket(), "[Server] nickname can't be empty\n", 34, 0);
		else if (!this->nicknameUsed(buffer))
		{
			this->_clients[this->_nbClient]->setNickname(buffer);
			break;
		}
		else
		{
			send(this->_clients[this->_nbClient]->getSocket(), "[Server] \"", 11, 0);
			send(this->_clients[this->_nbClient]->getSocket(), buffer, bytes_received - 1, 0);
			send(this->_clients[this->_nbClient]->getSocket(), "\" is already used by an other client\n", 38, 0);
		}
	}
}

void	Server::setUserClient(std::string user)
{
	char		buffer[1024] = {0};
	int			bytes_received;

	if (user.size())
	{
		send(this->_clients[this->_nbClient]->getSocket(), "[Server] Would you want to keep this username \"", 48, 0);
		send(this->_clients[this->_nbClient]->getSocket(), user.c_str(), user.size(), 0);
		send(this->_clients[this->_nbClient]->getSocket(), "\" ?\n[Server] yes or no ?\n", 24, 0);
		while (1)
		{
			if ((bytes_received = recv(this->_clients[this->_nbClient]->getSocket(), buffer, 1024, 0)) > 0)
				buffer[bytes_received] = '\0';
			if (bytes_received == 5 && buffer[0] == 'y' && buffer[1] == 'e' && buffer[2] == 's')
			{
				this->_clients[this->_nbClient]->setUsername(user);
				return ;
			}
			else if (bytes_received == 4 && buffer[0] == 'n' && buffer[1] == 'o')
				break ;
			else
				send(this->_clients[this->_nbClient]->getSocket(), "[Server] yes or no ?\n", 22, 0);
		}
	}
	send(this->_clients[this->_nbClient]->getSocket(), "[Server] Type your new username\n", 33, 0);
	while (1)
	{
		if ((bytes_received = recv(this->_clients[this->_nbClient]->getSocket(), buffer, 1024, 0)) > 0)
			buffer[bytes_received] = '\0';
		if (buffer[0] == '\n')
			send(this->_clients[this->_nbClient]->getSocket(), "[Server] username can't be empty\n", 34, 0);
		else if (!this->usernameUsed(buffer))
		{
			this->_clients[this->_nbClient]->setUsername(buffer);
			break;
		}
		else
		{
			send(this->_clients[this->_nbClient]->getSocket(), "[Server] \"", 11, 0);
			send(this->_clients[this->_nbClient]->getSocket(), buffer, bytes_received - 1, 0);
			send(this->_clients[this->_nbClient]->getSocket(), "\" is already used by an other client\n", 38, 0);
		}
	}
}

int	Server::nicknameUsed(std::string nick)
{
	for (unsigned int i = 0; i != this->_nbClient; i++)
	{
		if (this->_clients[i]->getNickname() == nick)
			return 1;
	}
	return 0;
}

int	Server::usernameUsed(std::string user)
{
	for (unsigned int i = 0; i != this->_nbClient; i++)
	{
		if (this->_clients[i]->getUsername() == user)
			return 1;
	}
	return 0;
}*/
