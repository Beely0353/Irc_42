/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:51:01 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/18 10:51:01 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

std::string Server::kick(std::vector<std::string> args, Client* client)
{
    std::string msg;

    if (!client->getAuthenticated()) {
        return "";
    } else if (args.size() < 3) {
        return this->msg461(client, "KICK");
    }

    std::string channelName = args[1];
    std::string targetNickname = args[2];
    std::string reason = args.size() > 3 ? args[3] : "";

    if (channelName.at(0) != '#') {
        return this->msg403(client, channelName);
    }

    if (this->_channels.find(channelName) == this->_channels.end()) {
        return this->msg403(client, channelName); 
    }

    Channel* channel = this->_channels[channelName];

    if (!channel->isOP(client->getUsername())) {
        return this->msg482(client, channelName);
    }

    Client* targetClient = findClientServerByNickname(targetNickname);
    if (!targetClient || !channel->isMember(targetClient->getUsername())) {
        return this->msg441(client, targetNickname, channelName);
    }

    channel->removeMember(targetClient);
    msg += ":" + client->getNickname() + " KICK " + channelName + " " + targetNickname;
    if (!reason.empty()) {
        msg += " :" + reason;
    }
    msg += "\r\n";

    //channel->SendMessChan(msg, channelName, client);
    //sendMessage(targetClient->getSocket(), "You have been kicked from " + channelName + " by " + client->getNickname());

    return msg;
}
