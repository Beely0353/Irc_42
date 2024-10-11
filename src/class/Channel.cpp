/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biaroun <biaroun@student.42nice.fr> >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:14:52 by biaroun           #+#    #+#             */
/*   Updated: 2024/10/11 13:35:26 by biaroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Channel.hpp"

Channel::Channel(Client *fonda, std::string name, std::string password) : _name(name), _password(password), _private(false), _maxClients(-1), _TopicChange(false)
{
    _members.insert(std::make_pair(fonda, "OP"));
}

Channel::~Channel() {}


void Channel::addMember(Client *client, std::string password)
{
    if (_password != password)
        return;
    if (_maxClients != -1 &&_members.size() >= _maxClients)
        return;
    _members.insert(std::make_pair(client, "USER"));
}

void Channel::removeMember(Client *client)
{

    _members.erase(client);
}

bool Channel::isOP(Client *client)
{
    if (_members[client] == "OP")
        return true;
    return false;
}

bool Channel::isInvited(Client *client)
{
    if (_invited.find(client) != _invited.end())
    {
        _invited.erase(client);
        return true;
    }
    return false;
}

bool Channel::isInviteOnly()
{
    if (_private)
        return true;
    return false;
}

bool Channel::isMember(Client *client)
{
    if (_members.find(client) != _members.end())
        return true;
    return false;
}

void Channel::ADDInvited(Client *client)
{
    _invited.insert(client);
}

void Channel::setMaxClients(int maxClients)
{
    _maxClients = maxClients;
}

void Channel::setTopicChange(bool b)
{
    _TopicChange = b;
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

std::string Channel::getPassword()
{
    return _password;
}

std::string Channel::getName()
{
    return _name;
}

std::string Channel::getTopic()
{
    return _topic;
}

bool Channel::isTopicProtected()
{
    return _TopicChange;
}

bool Channel::isFull()
{
    if (_maxClients != -1 && _members.size() >= _maxClients)
        return true;
    return false;
}

void Channel::OP(Client *client)
{
    _members[client] = "OP";
}

void Channel::DEOP(Client *client)
{
    _members[client] = "USER";
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

Client *Channel::findClient(std::string nick)
{
    for (std::map<Client*, std::string>::iterator it = _members.begin(); it != _members.end(); ++it) {
        Client* client = it->first;
        if (client->getNickname() == nick)
            return client;
    }
    return NULL;
}
