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

#include "../../include/Client.hpp"

Client::Client(int clientFd, struct sockaddr_in sockstruct)
{
	this->_socket = clientFd;
	this->_sockstruct = sockstruct;
	this->_nickname = "";
	this->_username = "";
	this->_pwd = false;
	this->_nick = false;
	this->_user = false;
	this->_hexchat = false;
}

Client::~Client()
{

}

void	Client::addChannel(std::string channel)
{
	this->_channels.push_back(channel);
}