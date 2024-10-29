/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:51:38 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/18 10:51:38 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

std::string	Server::nick(std::vector<std::string> arg, Client *client)
{
	if (!client->getPwd())
		return this->msg451(client, "NICK");
	if (arg[1].size())
	{
		if (client->getNick())
			return this->msg462(client);
		if (!this->nicknameUsed(arg[1]))
		{
			client->setNickname(arg[1]);
			client->setNick(true);
			if (client->getAuthenticated())
				return (this->msg001(client) + \
						this->msg002(client) + \
						this->msg003(client) + \
						this->msg004(client));
		}
		else
			return this->msg433(client, arg[1]);
	}
	else
		return this->msg461(client, "NICK");
	return "";
}