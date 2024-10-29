/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:03:24 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/16 14:03:24 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

std::string	Server::msg001(Client *client) {
	std::string	msg = this->getServerPrefix(client, "001") + ":Welcome to the ft_irc " + client->getNickname() + "\r\n";
	return msg;
}

std::string	Server::msg002(Client *client) {
	std::string	msg = this->getServerPrefix(client, "002") + ":Your host is " + this->getHostname() + ", running version " + this->getVersion() + "\r\n";
	return msg;
}

std::string	Server::msg003(Client *client) {
	std::string	msg = this->getServerPrefix(client, "003") + ":This server was created " + this->getDate() + "\r\n";
	return msg;
}

std::string	Server::msg004(Client *client) {
	std::string	msg = this->getServerPrefix(client, "004") + this->getHostname() + " " + this->getVersion() + " 0 itkol" + "\r\n";
	return msg;
}


std::string	Server::msg324(Client *client, std::string channel) {
	std::string	msg = this->getServerPrefix(client, "324") + channel + " " + this->msgmodechannel(channel) + "\r\n";
	return msg;
}

std::string	Server::msg329(Client *client, Channel *channel) {
	std::string	msg = this->getServerPrefix(client, "329") + channel->getName() + " " + channel->getTopic() + " " + channel->getDate() + "\r\n";
	return msg;
}

std::string	Server::msg332(Client *client, Channel *channel) {
	std::string	msg = this->getServerPrefix(client, "332") + channel->getName() + " :" + channel->getTopic() + "\r\n";
	return msg;
}

std::string	Server::msg333(Client *client, Channel *channel) {
	std::string	msg = this->getServerPrefix(client, "333") + channel->getName() + " " + channel->getTopicUser() + " " + channel->getTopicTime() + "\r\n";
	return msg;
}

std::string	Server::msg353(Client *client, std::string channel) {
	std::string	msg = this->getServerPrefix(client, "353") + "= " + channel + " :" + this->msgclientschannel(channel) + "\r\n";
	return msg;
}

std::string	Server::msg366(Client *client, std::string channel) {
	std::string	msg = this->getServerPrefix(client, "366") + channel + " :End of /NAMES list" + "\r\n";
	return msg;
}

std::string	Server::msg401(Client *client, std::string targetNickname) {
    std::string msg = this->getServerPrefix(client, "401") + " " + targetNickname + " :No such nick/channel\r\n";
    return msg;
}

std::string	Server::msg403(Client *client, std::string channel) {
	std::string	msg = this->getServerPrefix(client, "403") + client->getNickname() + " " + channel + " :No such channel" + "\r\n";
	return msg;
}

std::string Server::msg421(Client *client, std::string command) {
	std::string msg = this->getServerPrefix(client, "421") + " " + command + " :Unknown command\r\n";
	return msg;
}

std::string Server::msg331(Client *client, const std::string &channel) {
    std::string msg = this->getServerPrefix(client, "331") + client->getNickname() + " " + channel + " :No topic is set\r\n";
    return msg;
}


std::string	Server::msg433(Client *client, std::string nickname) {
	std::string	msg = this->getServerPrefix(client, "433") + " " + nickname + " :Nickname is already use" + "\r\n";
	return msg;
}

std::string Server::msg441(Client* client, const std::string& targetNick, const std::string& channelName) {
    return "441 " + client->getNickname() + " " + targetNick + " " + channelName + " :They are not on that channel\r\n";
}

std::string	Server::msg443(Client *client, std::string targetNickname, std::string channelName) {
    std::string msg = this->getServerPrefix(client, "443") + " " + targetNickname + " " + channelName + " :is already on channel\r\n";
    return msg;
}

std::string	Server::msg451(Client *client, std::string command) {
	std::string	msg = this->getServerPrefix(client, "451") + command + " :You have not registered" + "\r\n";
	return msg;
}

std::string	Server::msg461(Client *client, std::string command) {
	std::string	msg = this->getServerPrefix(client, "461") + command + " :Not enough parameters" + "\r\n";
	return msg;
}

std::string	Server::msg462(Client *client) {
	std::string	msg = this->getServerPrefix(client, "462") + " :You may not reregister" + "\r\n";
	return msg;
}

std::string	Server::msg464(Client *client) {
	std::string	msg = this->getServerPrefix(client, "464") + " :Password incorrect" + "\r\n";
	return msg;
}

std::string	Server::msg471(Client *client, std::string channel) {
	std::string	msg = this->getServerPrefix(client, "471") + channel + " :Cannot join channel (+l)" + "\r\n";
	return msg;
}

std::string Server::msg472(Client *client, std::string mode) {
    std::string msg = this->getServerPrefix(client, "472") + " " + mode + " :is unknown mode char\r\n";
    return msg;
}

std::string	Server::msg473(Client *client, std::string channel) {
	std::string	msg = this->getServerPrefix(client, "473") + channel + " :Cannot join channel (+i)" + "\r\n";
	return msg;
}

std::string	Server::msg475(Client *client, std::string channel) {
	std::string	msg = this->getServerPrefix(client, "475") + channel + " :Cannot join channel (+k)" + "\r\n";
	return msg;
}

std::string	Server::msg482(Client *client, std::string channelName) {
    std::string msg = this->getServerPrefix(client, "482") + " " + channelName + " :You're not channel operator\r\n";
    return msg;
}

std::string	Server::msg476(Client *client, std::string channel) {
	std::string	msg = this->getServerPrefix(client, "476") + channel + " :Bad Channel Mask" + "\r\n";
	return msg;
}

std::string Server::msgjoin(Client *client, std::string channel) {
	std::string msg = this->getUserPrefix(client) + "JOIN " + channel + "\r\n";
	return msg;
}

std::string Server::msgjoinop(Client *client, std::string channel) {
	std::string msg = ":" + this->getHostname() + " MODE " + channel + " +o " + client->getNickname() + "\r\n";
	return msg;
}
