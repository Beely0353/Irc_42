/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:40:54 by mgayout           #+#    #+#             */
/*   Updated: 2024/09/25 11:40:54 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

Client::Client() : _socket(0), _name("default"), _op(false)
{

}

Client::Client(int socket) : _socket(socket), _name("default"), _op(false)
{

}

Client& Client::operator=(const Client& other)
{
	if (other._socket)
		this->_socket = other._socket;
	return *this;
}

Client::~Client()
{

}


/**************************************************************************************************/

int Client::getSocket() const {
	return this->_socket;
}

std::string	Client::getNick() const {
	return this->_nick;
}

std::string	Client::getName() const {
	return this->_name;
}

void	Client::setNick(std::string nick) {
	this->_nick = nick;
}

void	Client::setUser(std::string user) {
	this->_user = user;
}

