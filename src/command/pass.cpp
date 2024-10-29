/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:51:31 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/18 10:51:31 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

std::string	Server::pass(std::vector<std::string> arg, Client *client)
{
	if (arg[1].size())
	{
		if (client->getPwd())
			return this->msg462(client);
		if (arg[1] == this->getPassword())
			client->setPwd(true);
		else
			return this->msg464(client);
	}
	else
		return this->msg461(client, "PASS");
	return "";
}