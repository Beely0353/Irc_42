/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:50:54 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/18 10:50:54 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

std::string Server::invite(std::vector<std::string> args, Client* client)
{
    std::string msg;

    if (!client->getAuthenticated()) {
        return "";
    } else if (args.size() < 3) {
        return this->msg461(client, "INVITE");
    }

    std::string targetNickname = args[1];
    std::string channelName = args[2];
    Client* targetClient = findClientServerByNickname(targetNickname);

    if (!targetClient) {
        return this->msg401(client, targetNickname);
    }

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

    if (channel->isMember(targetClient->getUsername())) {
        return this->msg443(client, targetNickname, channelName);
    }

    channel->addInvited(targetClient->getUsername());
    msg = ":" + client->getNickname() + " INVITE " + targetNickname + " " + channelName + "\r\n";
    //sendMessage(targetClient->getSocket(), msg);

    return msg;
}

