/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:51:18 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/18 10:51:18 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

std::string Server::mode(std::vector<std::string> args, Client *client)
{
    if (!client->getAuthenticated())
        return "";
    
    if (args.size() < 3)
        return msg461(client, "MODE");
    
    if (args[0] != "MODE")
        return msg421(client, args[0]);
    
    if (args[1].at(0) != '#') 
        return msg403(client, args[1]);

    if (args[2].at(0) != '+' && args[2].at(0) != '-')
        return msg472(client, args[2]);

    Channel *channel = this->_channels[args[1]];
    if (!channel) 
        return msg403(client, args[1]);

    std::string mode = args[2].substr(1);
    return modeOp(client, channel, mode, args);
}

std::string Server::modeOp(Client *client, Channel *channel, std::string mode, std::vector<std::string> args)
{
    if (!channel->isOP(client->getUsername()))
    {
        return msg482(client, channel->getName());
    }

    if (mode == "+i" || mode == "-i")
    {
        if (mode == "+i")
            channel->setPrivate(true);
        else
            channel->setPrivate(false);

        this->sendChannel(channel, "MODE " + channel->getName() + " " + mode);
        return "";
    }
    else if (mode == "+k" || mode == "-k")
    {
        if (mode == "+k")
        {
            if (args.size() < 4)
            {
                return msg461(client, "MODE");
            }
            channel->setPassword(args[3]);
            this->sendChannel(channel, "MODE " + channel->getName() + " +k " + args[3]);
        }
        else
        {
            channel->setPassword("");
            this->sendChannel(channel, "MODE " + channel->getName() + " -k");
        }
        return "";
    }
    else if (mode == "+l" || mode == "-l")
    {
        if (mode == "+l")
        {
            if (args.size() < 4)
            {
                return msg461(client, "MODE");
            }
            channel->setMaxClient(static_cast<unsigned int>(atoi(args[3].c_str())));
            this->sendChannel(channel, "MODE " + channel->getName() + " +l " + args[3]);
        }
        else
        {
            channel->setMaxClient(-1);
            this->sendChannel(channel, "MODE " + channel->getName() + " -l");
        }
        return "";
    }
    else if (mode == "+o" || mode == "-o")
    {
        if (args.size() < 4)
        {
            return msg461(client, "MODE");
        }
        std::string targetClient = args[3];
        if (channel->isMember(targetClient))
        {
            if (mode == "+o")
                channel->OP(targetClient);
            else
                channel->DEOP(targetClient);

            //channel->SendMessChanAll("MODE " + channel->getName() + " " + mode + " " + args[3], channel->getName());
        }
        else
        {
            return msg441(client, args[3], channel->getName());
        }
        return "";
    }
    else if (mode == "+t" || mode == "-t")
    {
        if (mode == "+t")
            channel->setTopicChange(false);  
        else
            channel->setTopicChange(true);

        this->sendChannel(channel, "MODE " + channel->getName() + " " + mode);
        return "";
    }
    else
    {
        return msg472(client, mode);
    }
}
