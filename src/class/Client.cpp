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

#include "../../include/ft_irc.hpp"

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

void	setNick(std::string nick) : _nick(nick) {}

void	setUser(std::string user) : _user(user) {}

