/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:51:46 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/18 10:51:46 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

std::string	Server::user(std::vector<std::string> arg, Client *client)
{
	if (!client->getPwd())
		return this->msg451(client, "USER");
	if (arg[1].size())
	{
		if (client->getUser())
			return this->msg462(client);
		if (!this->usernameUsed(arg[1]))
		{
			client->setUsername(arg[1]);
			client->setUser(true);
			if (client->getAuthenticated())
				return (this->msg001(client) + \
						this->msg002(client) + \
						this->msg003(client) + \
						this->msg004(client));
		}
	}
	else
		return this->msg461(client, "USER");
	return "";
}
