/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:48:08 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/18 10:48:08 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

std::string	Server::join(std::vector<std::string> arg, Client *client)
{
	std::vector<std::string>	channel, password;
	std::string					msg;

	if (!client->getAuthenticated())
		return "";
	else if (arg.size() == 1)
		return this->msg461(client, "JOIN");
	channel = split(arg[1], ',');
	if (arg.size() > 2)
		password = split(arg[2], ',');
	else
		password.push_back("");
	for (unsigned int i = 0; i < channel.size(); i++)
	{
		std::cout << "i = " << i << std::endl;
		if (password.size() < i)
			password.push_back("");
		if (channel[i][0] != '#')
		{
			msg += this->msg476(client, channel[i]);
			continue;
		}
		else if (!this->getChannel(channel[i]))
			msg += this->createChannel(channel[i], password[i], client);
		else
			msg += this->joinChannel(channel[i], password[i], client);
		msg += this->msg353(client, channel[i]) + this->msg366(client, channel[i]);
	}
	std::cout << msg << std::endl;
	return msg;
}

std::string	Server::createChannel(std::string channel, std::string password, Client *client)
{
	this->_channels[channel] = new Channel(client, channel, password);
	return (this->msgjoin(client, channel) + \
			this->msgjoinop(client, channel));
}

std::string	Server::joinChannel(std::string channel, std::string password, Client *client)
{
	std::string	msg = "";

	if (this->getChannel(channel)->getI() && this->getChannel(channel)->isInvited(client->getUsername()))
		return this->msg473(client, channel);
	else if (this->getChannel(channel)->getK() && this->getChannel(channel)->getPassword() != password)
		return this->msg475(client, channel);
	else if (this->getChannel(channel)->getL() && this->getChannel(channel)->getMembers().size() == this->getChannel(channel)->getMaxClient())
		return this->msg471(client, channel);
	if (this->getChannel(channel)->getTopic().size())
		msg = this->msg332(client, this->getChannel(channel)) + this->msg333(client, this->getChannel(channel));
	this->sendChannel(this->getChannel(channel), this->msgjoin(client, channel));
	this->getChannel(channel)->addClient(client->getUsername());
	this->getClient(client->getSocket())->addChannel(channel);
	return (this->msgjoin(client, channel) + msg);
}
