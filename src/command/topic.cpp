/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:52:57 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/18 10:52:57 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

std::string Server::topic(std::vector<std::string> args, Client *client) {
    if (!client->getAuthenticated())
        return "";

    if (args.size() < 2)
        return this->msg461(client, "TOPIC");

    std::string channelName = args[1];
    if (channelName[0] != '#')
        return this->msg403(client, channelName);

    Channel *channel = this->getChannel(channelName);
    if (!channel)
        return this->msg403(client, channelName);

    if (args.size() == 2) {
        if (channel->getTopic().empty())
            return this->msg331(client, channelName);
        else
            return this->msg332(client, channel) + this->msg333(client, channel);
    }

    std::string newTopic = args[2];
    if (args.size() > 3) {
        for (size_t i = 3; i < args.size(); i++) {
            newTopic += " " + args[i];
        }
    }

    if (channel->isTopicProtected() && !channel->isOP(client->getUsername()))
        return this->msg482(client, channelName);

    channel->setTopic(newTopic);
    this->sendChannel(channel, "TOPIC " + channel->getName() + " :" + newTopic);
    return ("TOPIC " + channel->getName() + " :" + newTopic);
}
