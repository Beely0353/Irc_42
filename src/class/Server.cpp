/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:39:51 by mgayout           #+#    #+#             */
/*   Updated: 2024/09/25 11:39:51 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

Server::Server(char *hostname, int port, std::string pwd)
{
	this->_hostname = hostname;
	this->_port = port;
	this->_password = pwd;
	this->_version = "ft_irc-1.0";
	this->_date = getCurrentDate();
	this->_nbClient = 1;
	this->_nbClientMax = 5;
	this->createSocket();
	this->_pfdstmp.fd = this->_socket;
	this->_pfdstmp.events = POLLIN;
	this->_pfds.push_back(this->_pfdstmp);
	this->launching();
}

Server::~Server()
{
	close(this->_socket);
}

void	Server::createSocket()
{
	if ((this->_socket = socket(AF_INET, SOCK_STREAM, 0)) <= 0)
		throw (Server::SocketCreationError());
	this->_sockstruct.sin_family = AF_INET;
	this->_sockstruct.sin_addr.s_addr = INADDR_ANY;
	this->_sockstruct.sin_port = htons(this->getPort());
	if (bind(this->getSocket(), (struct sockaddr *)&this->getSockstruct(), sizeof(this->getSockstruct())) < 0)
		throw (Server::SocketBindError());
	if (listen(this->getSocket(), this->getNbClientMax()) < 0)
		throw (Server::SocketListenError());
}

void	Server::launching()
{
	std::cout << "[Server] Waiting for connections on port " << this->getPort() << "..." << std::endl;

	while (1)
	{
		if (poll(this->_pfds.data(), this->_pfds.size(), -1) == -1)
			throw (Server::pollException());
		for (unsigned int i = 0; i < this->_pfds.size(); i++)
		{
			if (!this->_pfds[i].revents)
				continue;
			if (!(this->_pfds[i].revents & POLLIN))
				continue;
			if (this->_pfds[i].fd == this->getSocket())
				this->addClient();
			else
				this->clientRequest(i);
			break;
		}
	}
}

void	Server::addClient()
{
	struct sockaddr_in		sockstruct;
	int						clientFd;
	socklen_t				structlen = sizeof(sockstruct);

	if (this->_nbClient == this->_nbClientMax)
		std::cout << "Error: can't accept new client because server is full" << std::endl;
	else if ((clientFd = accept(this->_socket, (struct sockaddr*)&sockstruct, &structlen)) == -1)
		std::cout << "Error: fail to accept new client" << std::endl;
	else
	{
		this->_pfdstmp.fd = clientFd;
		this->_pfds.push_back(this->_pfdstmp);
		this->_clients.insert(std::pair<int, Client *>(clientFd, new Client(clientFd, sockstruct)));
		std::cout << "[Server] New client has been add" << std::endl;
		this->_nbClient++;
	}
}

void	Server::clientRequest(unsigned int idClient)
{
	int			clientFd = this->getPollfd(idClient);
	char		buffer[1024];
	int			bytes_received, line = 0;
	std::string	buf, msg;

	bytes_received = recv(clientFd, buffer, sizeof(buffer), 0);
	if (bytes_received <= 0)
		throw (Server::RecvError());
	else
	{
		buffer[bytes_received] = '\0';
		buf = buffer;
		for (int i = 0; i < bytes_received; i++)
			if (buf[i] == '\n')
				line++;
		for (int i = 0; i != line; i++)
		{
			msg = this->commands(this->splitBuffer(buf), clientFd);
			if (msg.size())
				send(clientFd, msg.c_str(), msg.size(), 0);
			buf = buf.substr(buf.find('\n') + 1);
		}
	}
}

std::string	Server::commands(std::vector<std::string> buffer, int clientFd)
{
	std::string	commands[17] = {"JOIN", "PART", "KICK", "INVITE", "TOPIC", "MODE", "CAP", "PASS", "NICK", "USER", "OP", "DEOP", "MSG", "QUIT", "SENDFILE", "GETFILE", "BOT"};
	int			i = -1;

	for (unsigned int j = 0; j < buffer.size(); j++)
		std::cout << "buffer[" << j << "] = " << buffer[j] << std::endl;

	while (++i < 18)
		if (buffer[0] == commands[i])
			break ;
	std::cout << i << std::endl;
	switch (i)
	{
	case 0:
			return this->join(buffer, this->_clients[clientFd]);
	case 1:
			return this->part(buffer, this->_clients[clientFd]);
	case 2:
			return this->kick(buffer, this->_clients[clientFd]);
	case 3:
			return this->invite(buffer, this->_clients[clientFd]);
	case 4:
			return this->topic(buffer, this->_clients[clientFd]);
	case 5:
			return this->mode(buffer, this->_clients[clientFd]);
	case 6:
			return this->cap(this->_clients[clientFd]);
	case 7:
			return this->pass(buffer, this->_clients[clientFd]);
	case 8:
			return this->nick(buffer, this->_clients[clientFd]);
	case 9:
			return this->user(buffer, this->_clients[clientFd]);
	case 10:
			return this->op(buffer, this->_clients[clientFd]);
	case 11:
			return this->deop(buffer, this->_clients[clientFd]);
	case 12:
			return this->msg(buffer, this->_clients[clientFd]);
	case 13:
			return this->quit(this->_clients[clientFd]);
	case 14:
			return this->sendfile(buffer, this->_clients[clientFd]);
	case 15:
			return this->getfile(buffer, this->_clients[clientFd]);
	case 16:
			return this->bot(buffer, this->_clients[clientFd]);
	default:
			return "";
	}
	return "";
}

Client *Server::findClientServerByUsername(std::string Username) {
    for (std::map<int, Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
        if (it->second->getUsername() == Username) {
            return it->second;
        }
    }
    return NULL;
}


Client *Server::findClientServerByNickname(const std::string &nickname) {
    for (std::map<int, Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
        if (it->second->getNickname() == nickname) {
            return it->second;
        }
    }
    return NULL;
}

