/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:50:45 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/18 10:50:45 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"


std::string Server::part(std::vector<std::string> arg, Client *client)
{
    std::vector<std::string> channel;
    std::string msg;

    if (!client->getAuthenticated())
        return "";

    if (arg.size() == 1)
        return this->msg461(client, "PART");

    channel = split(arg[1], ',');

    for (unsigned int i = 0; i < channel.size(); i++)
    {
        if (channel[i][0] != '#')
        {
            msg += this->msg403(client, channel[i]);
            continue;
        }

        if (this->_channels.find(channel[i]) != this->_channels.end())
        {
            std::string partMsg = client->getNickname() + " has left " + channel[i];
            this->_channels[channel[i]]->removeMember(client);
            //this->_channels[channel[i]]->SendMessChan(partMsg, channel[i], client);
        }
            msg += this->msg403(client, channel[i]);
    }

    return msg;
}

std::string Server::partDefault(std::string arg, Client *client)
{
    std::string msg;

    if (this->_channels.find(arg) != this->_channels.end())
    {
        std::string partMsg = client->getNickname() + " has left " + arg;
        this->_channels[arg]->removeMember(client);
        //this->_channels[arg]->SendMessChan(partMsg, arg, client);
    }
    else
        return this->msg403(client, arg);

    return msg;
}

std::string Server::partReason(std::string arg, Client *client)
{
    std::string channelName = arg.substr(0, arg.find(" "));
    std::string reason = arg.substr(arg.find(" ") + 1);
    std::string msg;

    if (this->_channels.find(channelName) != this->_channels.end())
    {
        std::string partMsg = client->getNickname() + " has left " + channelName + " (" + reason + ")";
        this->_channels[channelName]->removeMember(client);
        //this->_channels[channelName]->SendMessChan(partMsg, channelName, client);
    }
    else
        return this->msg403(client, channelName);
    return msg;
}
