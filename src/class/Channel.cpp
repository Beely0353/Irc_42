/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biaroun <biaroun@student.42nice.fr> >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:14:52 by biaroun           #+#    #+#             */
/*   Updated: 2024/10/29 17:01:07 by biaroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Channel.hpp"

Channel::Channel(Client *client, std::string name, std::string password)
{
	this->_name = name;
	this->_password = password;
	this->_topic = "";
	this->_i = false;
	this->_t = false;
	this->_k = false;
	if (this->getPassword().size())
		this->_k = true;
	this->_l = false;
	this->_maxClient = 1;
	this-> _topicChange = false;
	this->_date = getCurrentDate();
    _members.insert(std::pair<std::string, bool>(client->getUsername(), true));
}

Channel::~Channel() {}

bool	Channel::isInvited(std::string username)
{
	for (unsigned int i = 0; i < this->_invited.size(); i++)
	{
		if (this->_invited[i] == username)
			return true;
	}
	return false;
}

void	Channel::addClient(std::string username)
{
	this->_members.insert(std::pair<std::string, bool>(username, false));
}

bool Channel::isMember(std::string client)
{
    if (_members.find(client) != _members.end())
        return true;
    return false;
}

bool Channel::isOP(std::string client)
{
    if (_members[client] == true)
        return true;
    return false;
}

void Channel::setPrivate(bool priv)
{
    _private = priv;
}

void Channel::setPassword(std::string password)
{
	_password = password;
}

int Channel::removeMember(Client* client) {
    std::map<std::string, bool>::iterator it = _members.find(client->getUsername());
    
    if (it != _members.end()) {
        _members.erase(it);
        return 0;
    }
    
    return 1;
}

void Channel::OP(std::string client)
{
	_members[client] = true;
}

void Channel::DEOP(std::string client)
{
	_members[client] = false;
}

void Channel::setTopicChange(bool change)
{
	_topicChange = change;
}


void Channel::addInvited(std::string client)
{
    _invited.push_back(client);
}

bool Channel::isTopicProtected()
{
    return _topicChange;
}

/*Client *Channel::findClientChannel(std::string Username)
{
	std::map<std::string, bool>::iterator it = _members.find(Username);
	
    if (it != _members.end()) {
        return ;
    }
    
    return 1;
}*/
