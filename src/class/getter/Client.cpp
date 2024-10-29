/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:39:02 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/16 11:39:02 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Client.hpp"

const int					&Client::getSocket() {return this->_socket;}
const struct sockaddr_in	&Client::getSockstruct() {return this->_sockstruct;}
const std::string			&Client::getNickname() {return this->_nickname;}
const std::string			&Client::getUsername() {return this->_username;}
const bool					&Client::getPwd() {return this->_pwd;}
const bool					&Client::getNick() {return this->_nick;}
const bool					&Client::getUser() {return this->_user;}
const bool					&Client::getHexchat() {return this->_hexchat;}

bool						Client::getAuthenticated()
{
	if (this->getPwd() && this->getNick() && this->getUser())
		return true;
	return false;
}