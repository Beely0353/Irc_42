/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:51:08 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/18 10:51:08 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

std::string	Server::quit(Client *client)
{
	if (!client->getAuthenticated())
		return "";
	for (unsigned int i = 0; i < this->_pfds.size(); i++)
	{
		if (this->_pfds[i].fd == client->getSocket())
		{
			std::cout << "Client n°" << i << " has been disconnected\n";
			close (this->_pfds[i].fd);
			close(client->getSocket());
			this->_pfds.erase(this->_pfds.begin() + i);
			this->_clients.erase(client->getSocket());
			this->_nbClient--;
			break;
		}
	}
	return "";
}