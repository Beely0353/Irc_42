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
		this->_clients[clientFd]->setNickname(arg);
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

/*************************************************** */

void	Server::mode(std::string arg, int clientFd)
{
	std::vector<std::string> args = split(arg, ' ');
	if (args.size() < 2)
	{
		sendMessage(clientFd, "ERR_NEEDMOREPARAMS: Not enough parameters for MODE");
		return;
	}
	if (args[0] != "MODE")
	{
		sendMessage(clientFd, "ERR_UNKNOWNCOMMAND: Unknown command");
		return;
	}
	if (args[1].at(0) != '#') 
	{
		sendMessage(clientFd, "ERR_NOSUCHCHANNEL: Invalid channel name");
		return;
	}
	if (args[2].at(0) != '+' && args[2].at(0) != '-')
	{
		sendMessage(clientFd, "ERR_UNKNOWNMODE: Unknown mode");
		return;
	}
	Channel *channel = this->_channels[args[1]];
	Client  *client = this->_clients[clientFd];
	std::string mode = args[2].substr(1);
	modeOp(client, channel, mode, args);
}

void	Server::modeOp(Client *client, Channel *channel, std::string mode, std::vector<std::string> args)
{
	int clientFd = client->getSocket();

	if (!channel->isOP(client))
	{
		sendMessage(clientFd, "ERR_CHANOPRIVSNEEDED: You're not channel operator");
		return;
	}

	if (mode == "+i" || mode == "-i")
	{
		if (mode == "+i")
			channel->setPrivate(true);
		else
			channel->setPrivate(false);

		channel->SendMessChanAll("MODE " + channel->getName() + " " + mode, channel->getName());
	}

	else if (mode == "+k" || mode == "-k")
	{
		if (mode == "+k")
		{
			if (args.size() < 4)
			{
				sendMessage(clientFd, "ERR_NEEDMOREPARAMS: Not enough parameters for MODE");
				return;
			}
			channel->setPassword(args[3]);
			channel->SendMessChanAll("MODE " + channel->getName() + " +k " + args[3], channel->getName());
		}
		else
		{
			channel->setPassword("");
			channel->SendMessChanAll("MODE " + channel->getName() + " -k", channel->getName());
		}
	}

	else if (mode == "+l" || mode == "-l")
	{
		if (mode == "+l")
		{
			if (args.size() < 4)
			{
				sendMessage(clientFd, "ERR_NEEDMOREPARAMS: Not enough parameters for MODE");
				return;
			}
			channel->setMaxClients(std::stoi(args[3]));
			channel->SendMessChanAll("MODE " + channel->getName() + " +l " + args[3], channel->getName());
		}
		else
		{
			channel->setMaxClients(-1);
			channel->SendMessChanAll("MODE " + channel->getName() + " -l", channel->getName());
		}
	}


	else if (mode == "+o" || mode == "-o")
	{
		if (args.size() < 4)
		{
			sendMessage(clientFd, "ERR_NEEDMOREPARAMS: Not enough parameters for MODE");
			return;
		}
		Client *targetClient = findClient(args[3]);
		if (channel->isMember(targetClient))
		{
			if (mode == "+o")
				channel->OP(targetClient);
			else
				channel->DEOP(targetClient);

			channel->SendMessChanAll("MODE " + channel->getName() + " " + mode + " " + args[3], channel->getName());
		}
		else
		{
			sendMessage(clientFd, "ERR_USERNOTINCHANNEL: User is not in the channel");
		}
	}

	else if (mode == "+t" || mode == "-t")
	{
		if (mode == "+t")
			channel->setTopicChange(false);  
		else
			channel->setTopicChange(true);

		channel->SendMessChanAll("MODE " + channel->getName() + " " + mode, channel->getName());
	}

	// Mode inconnu
	else
	{
		sendMessage(clientFd, "ERR_UNKNOWNMODE: Unknown mode");
		return;
	}
}


/*************************************************** */

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
		Channel *channel = this->_channels[arg.substr(0, arg.find(" "))];
		if (channel->isFull())
		{
			sendMessage(clientFd, "ERR_CHANNELISFULL: " + arg.substr(0, arg.find(" ")) + "is full");
			continue;
		}
		if (args[i].find(" ") != std::string::npos)
			JoinPsswrd(args[i], clientFd);
		else if (channel->isInviteOnly() && channel->isInvited(this->_clients[clientFd]))
			joinDefault(args[i], clientFd);
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
		this->_channels[channelName]->addMember(this->_clients[clientFd], password);
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
		this->_channels[arg]->addMember(this->_clients[clientFd], "");
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
	std::string msg = this->_clients[clientFd]->getNickname() + " has left " + arg;
	if(this->_channels.find(arg) != this->_channels.end())
	{
		this->_channels[arg]->removeMember(this->_clients[clientFd]);
		_channels[arg]->SendMessChan(msg, arg, this->_clients[clientFd]);
	}
	else
		sendMessage(clientFd, "ERR_NOSUCHCHANNEL: Invalid channel name");
}

void	Server::partReason(std::string arg, int clientFd)
{
	std::string channelName = arg.substr(0, arg.find(" "));
	std::string reason = arg.substr(arg.find(" ") + 1);
	std::string msg = this->_clients[clientFd]->getNickname() + " has left " + channelName +"(" + reason + ")";

	if(this->_channels.find(arg) != this->_channels.end())
	{
		this->_channels[channelName]->removeMember(this->_clients[clientFd]);
		this->_channels[channelName]->SendMessChan(msg, channelName, this->_clients[clientFd]);
	}
	else
		sendMessage(clientFd, "ERR_NOSUCHCHANNEL: Invalid channel name");
}

/*************************************************** */
void	Server::kick(std::string arg, int clientFd)
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
			kickReason(args[i], clientFd);
		else
			kickDefault(args[i], clientFd);
	}
}

void	Server::kickDefault(std::string arg, int clientFd)
{
	std::string channelName = arg.substr(0, arg.find(" "));
	std::string nickname = arg.substr(arg.find(" ") + 1);

	if (this->_channels.find(channelName) != this->_channels.end())
	{
		Channel* channel = this->_channels[channelName];

		if (channel->isOP(this->_clients[clientFd]))
		{
			Client* targetClient = findClient(nickname);
			if (targetClient && channel->isMember(targetClient))
			{
				channel->removeMember(targetClient);
				channel->SendMessChan(nickname + " has been kicked by " + this->_clients[clientFd]->getNickname(), channelName, this->_clients[clientFd]);
				sendMessage(targetClient->getSocket(), "You have been kicked from " + channelName + " by " + this->_clients[clientFd]->getNickname());
			}
			else
			{
				sendMessage(clientFd, "ERR_USERNOTINCHANNEL: User is not in the channel");
			}
		}
		else
			sendMessage(clientFd, "ERR_CHANOPRIVSNEEDED: You're not channel operator");
	}
	else
		sendMessage(clientFd, "ERR_NOSUCHCHANNEL: Invalid channel name");
}

void	Server::kickReason(std::string arg, int clientFd)
{
	std::string channelName = arg.substr(0, arg.find(" "));
	std::string nickname = arg.substr(arg.find(" ") + 1, arg.find(" :") - (arg.find(" ") + 1));
	std::string reason = arg.substr(arg.find(" :") + 2);

	if (this->_channels.find(channelName) != this->_channels.end())
	{
		Channel* channel = this->_channels[channelName];

		if (channel->isOP(this->_clients[clientFd]))
		{
			Client* targetClient = findClient(nickname);
			if (targetClient && this->_channels[channelName]->isMember(targetClient))
			{
				channel->removeMember(targetClient);
				channel->SendMessChan(nickname + " has been kicked by " + this->_clients[clientFd]->getNickname() + " (" + reason + ")", channelName, this->_clients[clientFd]);
				sendMessage(targetClient->getSocket(), "You have been kicked from " + channelName + " by " + this->_clients[clientFd]->getNickname());
			}
			else
			{
				sendMessage(clientFd, "ERR_USERNOTINCHANNEL: User is not in the channel");
			}
		}
		else
			sendMessage(clientFd, "ERR_CHANOPRIVSNEEDED: You're not channel operator");
	}
	else
		sendMessage(clientFd, "ERR_NOSUCHCHANNEL: Invalid channel name");
}

/*************************************************** */
void	Server::invite(std::string arg, int clientFd)
{
	std::vector<std::string> args = split(arg, ' ');
	Client *targetClient = findClient(args[1]);

	if (args[0] != "INVITE")
	{
		sendMessage(clientFd, "ERR_UNKNOWNCOMMAND: Unknown command");
		return;
	}
	if (args.size() < 3)
    {
        sendMessage(clientFd, "ERR_NEEDMOREPARAMS: Not enough parameters for INVITE");
        return;
    }
	if (!this->isClient(targetClient))
	{
		sendMessage(clientFd, "ERR_NOSUCHNICK: No such nick/channel");
		return;
	}
	if (args[2].at(0) != '#') 
	{
		sendMessage(clientFd, "ERR_NOSUCHCHANNEL: Invalid channel name");
		return;
	}
	if (this->_channels.find(args[2]) == this->_channels.end())
	{
		sendMessage(clientFd, "ERR_NOSUCHCHANNEL: No such channel");
		return;
	}
	if (!this->_channels[args[2]]->isOP(this->_clients[clientFd]))
	{
        sendMessage(clientFd, "ERR_CHANOPRIVSNEEDED: You're not a channel operator");
        return;
	}

	if (this->_channels[args[2]]->isMember(targetClient))
	{
		sendMessage(clientFd, "ERR_USERONCHANNEL: " + args[1] + " is already on " + args[2]);
		return;
	}


	this->_channels[args[2]]->ADDInvited(targetClient);
	sendMessage(targetClient->getSocket(), ":" + this->_clients[clientFd]->getNickname() + " INVITE " + args[1] + " " + args[2]);
	return;
}


/*************************************************** */
void	Server::topic(std::string arg, int clientFd)
{
	std::vector<std::string> args = split(arg, ' ');

	if (args.size() < 2) 
	{
		sendMessage(clientFd, "ERR_NEEDMOREPARAMS: Not enough parameters for TOPIC");
		return;
	}

	std::string channelName = args[1];
	if (channelName.at(0) != '#') 
	{
		sendMessage(clientFd, "ERR_NOSUCHCHANNEL: Invalid channel name");
		return;
	}
	if (this->_channels.find(channelName) == this->_channels.end())
	{
		sendMessage(clientFd, "ERR_NOSUCHCHANNEL: No such channel");
		return;
	}

	Channel *channel = this->_channels[channelName];
	if (args.size() == 2) 
	{
		sendMessage(clientFd, "RPL_TOPIC: " + channel->getName() + " :" + channel->getTopic());
		return;
	}

	if (args.size() >= 3) 
	{
		std::string newTopic = arg.substr(arg.find(' ', arg.find(' ') + 1) + 1);

		if (channel->isTopicProtected() && !channel->isOP(this->_clients[clientFd])) 
		{
			sendMessage(clientFd, "ERR_CHANOPRIVSNEEDED: You're not a channel operator");
			return;
		}
		channel->setTopic(newTopic);
		channel->SendMessChanAll("TOPIC " + channel->getName() + " :" + newTopic, channel->getName());
	}
}

/*************************************************** */

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
