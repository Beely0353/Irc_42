/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biaroun <biaroun@student.42nice.fr> >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:14:52 by biaroun           #+#    #+#             */
/*   Updated: 2024/10/03 13:05:20 by biaroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Channel.hpp"

Channel::Channel(Client *fonda, std::string name, std::string password) : _name(name), _password(password), _private(false), _maxClients(0)
{
    _members.insert(std::make_pair(fonda, OP));
}

Channel::~Channel() {}


void Channel::addMember(Client *client, std::string password)
{
    if (_password != password)
        return;
    _members.insert(std::make_pair(client, 0));
}

void Channel::removeMember(Client *client)
{

    _members.erase(client);
}

bool Channel::isOP(Client *client)
{
    if (_members[client] == OP)
        return true;
    return false;
}

void Channel::setTopic(std::string topic)
{
    _topic = topic;
}

void Channel::setPassword(std::string password)
{
    _password = password;
}

void Channel::setPrivate(bool priv)
{
    _private = priv;
}

bool Channel::getPrivate()
{
    return _private;
}

void	Channel::SendMessChanAll(std::string msg, std::string chanName)
{
	for (std::map<Client*, std::string>::iterator it = _members.begin(); it != _members.end(); ++it) {
        Client* client = it->first;
		sendMessage(client->getSocket(), msg);
	}
}

void	Channel::SendMessChan(std::string msg, std::string chanName, Client *send)
{
	for (std::map<Client*, std::string>::iterator it = _members.begin(); it != _members.end(); ++it) {
        Client* client = it->first;
		if (client == send)
			continue;
		sendMessage(client->getSocket(), msg);
	}
}
