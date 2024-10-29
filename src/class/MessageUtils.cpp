/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageUtils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:33:35 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/18 13:33:35 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

std::string	Server::getUserPrefix(Client *client) {
	std::string	prefix = ":" + client->getNickname() + "!" + client->getUsername() + "@" + this->getHostname() + " ";
	return prefix;
}

std::string	Server::getServerPrefix(Client *client, std::string code) {
	std::string	prefix = ":" + this->getHostname() + " " + code + " " + client->getNickname() + " ";
	return prefix;
}

std::string	Server::msgclientschannel(std::string channel)
{
	Channel	*tmp = this->getChannel(channel);
	std::string msg;

	for (std::map<std::string, bool>::iterator it = tmp->getMembers().begin(); it != tmp->getMembers().end(); ++it)
	{
		if (it->second)
			msg += "@" + it->first;
		else
			msg += " " + it->first;
	}
	return msg;
}

std::string	Server::msgmodechannel(std::string channel) //to complete
{
	std::string msg;

	if (this->getChannel(channel)->getI())
		msg += "i";
	if (this->getChannel(channel)->getT())
		msg += "t";
	if (this->getChannel(channel)->getK())
		msg += "k";
	if (this->getChannel(channel)->getL())
		msg += "l";
	return msg;
}