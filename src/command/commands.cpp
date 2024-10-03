/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:42:54 by mgayout           #+#    #+#             */
/*   Updated: 2024/09/27 17:42:54 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

void	Server::pass(std::string arg, int clientFd)
{
	if (arg != this->_password)
		std::cout << "bad mdp" << std::endl;
	else
		this->_clients[clientFd]->setAuthenticated(true);
}

void	Server::nick(std::string arg, int clientFd)
{
	if (arg != this->_password)
		std::cout << "bad mdp" << std::endl;
	else
		this->_clients[clientFd]->setNicknames(arg);
}

void	Server::user(std::string arg, int clientFd)
{
	if (arg != this->_password)
		std::cout << "bad mdp" << std::endl;
	else
		this->_clients[clientFd]->setUsername(arg);
}

void	Server::oper(std::string arg, int clientFd)
{
	if (arg != this->_password)
		std::cout << "bad mdp" << std::endl;
	else
		this->_clients[clientFd]->setAuthenticated(true);
}

void	Server::mode(std::string arg, int clientFd, std::string chanName)
{
	if (this->_clients[clientFd]->get)
		std::cout << "bad mdp" << std::endl;
	else
	{
		if (strcmp(arg.substr(0,2), "+i") || strcmp(arg.substr(0,2), "-i"))
			this->PrivateChannel(arg, channelFd);
	}
}

void	Server::PrivateChannel(std::string arg, unsigned int channelFd)
{
	if (strcmp(arg.substr(0,2), "+i"))
		this->_channels[channelFd]->setPrivate(true);
	else if (strcmp(arg.substr(0,2), "-i"))
		this->_channels[channelFd]->setPrivate(false);
}

void	Server::quit(std::string arg, int clientFd)
{
	if (arg != this->_password)
		std::cout << "bad mdp" << std::endl;
	else
		this->_clients[clientFd]->setAuthenticated(true);
}
/*************************************************** */
void	Server::Join(std::string arg, int clientFd)
{
	std::vector<std::string> args = split(arg, ',');
	for (size_t i = 0; i < args.size(); i++)
	{
		if (args[i].at(0) != '#') 
		{
			sendMessage(clientFd, "ERR_NOSUCHCHANNEL: Invalid channel name");
			continue;
		}
		if (args[i].find(" ") != std::string::npos)
			JoinPsswrd(args[i], clientFd);
		else
			joinDefault(args[i], clientFd);
	}

}

void	Server::JoinPsswrd(std::string arg, int clientFd)
{
	std::string channelName = arg.substr(0, arg.find(" "));
	std::string password = arg.substr(arg.find(" ") + 1);

	if(this->_channels.find(arg) != this->_channels.end())
	{
		if (this->_channels[channelName]->getPassword() != password)
		{
			sendMessage(clientFd, "ERR_BADCHANNELKEY: Invalid channel key");
			return;
		}
		this->_channels[channelName].addMember(this->_clients[clientFd]);
	}
	else
	{
		Channel *newChannel = new Channel(this->_clients[clientFd], arg, password);
		this->_channels.insert(std::make_pair(channelName, newChannel));
	}
}

void	Server::joinDefault(std::string arg, int clientFd)
{
	if(this->_channels.find(arg) != this->_channels.end())
		this->_channels[arg].addMember(this->_clients[clientFd]);
	else
	{
		Channel *newChannel = new Channel(this->_clients[clientFd], arg, "");
		this->_channels.insert(std::make_pair(arg, newChannel));
	}
}

/*************************************************** */
void	Server::part(std::string arg, int clientFd)
{
	std::vector<std::string> args = split(arg, ',');
	for (size_t i = 0; i < args.size(); i++)
	{
		if (args[i].at(0) != '#') 
		{
			sendMessage(clientFd, "ERR_NOSUCHCHANNEL: Invalid channel name");
			continue;
		}
		if (args[i].find(" :") != std::string::npos)
			partReason(args[i], clientFd);
		else
			partDefault(args[i], clientFd);
	}
}

void	Server::partDefault(std::string arg, int clientFd)
{
	std::string msg = this->Clients[clientFd]->getNicknames() + " has left " + arg;
	if(this->_channels.find(arg) != this->_channels.end())
	{
		this->_channels[arg].removeMember(this->_clients[clientFd]);
		_channels[arg].SendMessChan(msg, arg, this->_clients[clientFd]);
	}
	else
		sendMessage(clientFd, "ERR_NOSUCHCHANNEL: Invalid channel name");
}

void	Server::partReason(std::string arg, int clientFd)
{
	std::string channelName = arg.substr(0, arg.find(" "));
	std::string reason = arg.substr(arg.find(" ") + 1);
	std::string msg = this->Clients[clientFd]->getNicknames() + " has left " + channelName +"(" + reason + ")";

	if(this->_channels.find(arg) != this->_channels.end())
	{
		this->_channels[channelName].removeMember(this->_clients[clientFd]);
		_channels[channelName].SendMessChan(msg, channelName, this->_clients[clientFd]);
	}
	else
		sendMessage(clientFd, "ERR_NOSUCHCHANNEL: Invalid channel name");
}

/*************************************************** */
void	Server::topic(std::string arg, int clientFd)
{
	if (arg != this->_password)
		std::cout << "bad mdp" << std::endl;
	else
		this->_clients[clientFd]->setAuthenticated(true);
}

void	Server::kick(std::string arg, int clientFd)
{
	if (arg != this->_password)
		std::cout << "bad mdp" << std::endl;
	else
		this->_clients[clientFd]->setAuthenticated(true);
}

void	Server::privmsg(std::string arg, int clientFd)
{
	if (arg != this->_password)
		std::cout << "bad mdp" << std::endl;
	else
		this->_clients[clientFd]->setAuthenticated(true);
}

void	Server::notice(std::string arg, int clientFd)
{
	if (arg != this->_password)
		std::cout << "bad mdp" << std::endl;
	else
		this->_clients[clientFd]->setAuthenticated(true);
}

void	Server::sendfile(std::string arg, int clientFd)
{
	if (arg != this->_password)
		std::cout << "bad mdp" << std::endl;
	else
		this->_clients[clientFd]->setAuthenticated(true);
}

void	Server::getfile(std::string arg, int clientFd)
{
	if (arg != this->_password)
		std::cout << "bad mdp" << std::endl;
	else
		this->_clients[clientFd]->setAuthenticated(true);
}

void	Server::bot(std::string arg, int clientFd)
{
	if (arg != this->_password)
		std::cout << "bad mdp" << std::endl;
	else
		this->_clients[clientFd]->setAuthenticated(true);
}

void	Server::cap(int clientFd)
{
	this->_clients[clientFd]->setHexchat(true);
	std::cout << "hexchat" << std::endl;
}
