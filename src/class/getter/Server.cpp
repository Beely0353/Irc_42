/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:13:03 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/16 11:13:03 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

const std::string			&Server::getHostname() {return this->_hostname;}
const int					&Server::getPort() {return this->_port;}
const std::string			&Server::getPassword() {return this->_password;}
const std::string			&Server::getVersion() {return this->_version;}
const std::string			&Server::getDate() {return this->_date;}
const unsigned int			&Server::getNbClient() {return this->_nbClient;}
const unsigned int			&Server::getNbClientMax() {return this->_nbClientMax;}
const int					&Server::getSocket() {return this->_socket;}
const struct sockaddr_in	&Server::getSockstruct() {return this->_sockstruct;}
const int					&Server::getPollfd(int idClient) {return this->_pfds[idClient].fd;}
Client						*Server::getClient(int clientFd) {return this->_clients[clientFd];}
Channel						*Server::getChannel(std::string channel) {return this->_channels[channel];}