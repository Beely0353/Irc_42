/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:05:57 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/16 14:05:57 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP

# include "Utils.hpp"

std::string		join(std::vector<std::string> arg, Client *client);
std::string		createChannel(std::string channel, std::string password, Client *client);
std::string		joinChannel(std::string channel, std::string password, Client *client);

std::string		joinPsswrd(std::vector<std::string> arg, Client *client);
std::string		joinDefault(std::vector<std::string> arg, Client *client);
std::string		part(std::vector<std::string> arg, Client *client);
std::string		partDefault(std::string arg, Client *client);
std::string		partReason(std::string arg, Client *client);
std::string		kick(std::vector<std::string> arg, Client *client);
std::string		kickDefault(std::vector<std::string> arg, Client *client);
std::string		kickReason(std::vector<std::string> arg, Client *client);
std::string		invite(std::vector<std::string> arg, Client *client);
std::string		topic(std::vector<std::string> arg, Client *client);
std::string		mode(std::vector<std::string> arg, Client *client);
std::string		modeOp(Client *client, Channel *channel, std::string mode, std::vector<std::string> args);
std::string		cap(Client *client);
std::string		pass(std::vector<std::string> arg, Client *client);
std::string		nick(std::vector<std::string> arg, Client *client);
std::string		user(std::vector<std::string> arg, Client *client);
std::string		op(std::vector<std::string> arg, Client *client);
std::string		deop(std::vector<std::string> arg, Client *client);
std::string		msg(std::vector<std::string> arg, Client *client);
std::string		quit(Client *client);
std::string		sendfile(std::vector<std::string> arg, Client *client);
std::string		getfile(std::vector<std::string> arg, Client *client);
std::string		bot(std::vector<std::string> arg, Client *client);

#endif
