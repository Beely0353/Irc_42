/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:20:07 by mgayout           #+#    #+#             */
/*   Updated: 2024/09/25 11:20:07 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_HPP
# define FT_IRC_HPP

#include <iostream>
#include <algorithm>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <string>   

class	Client
{
	public:
			Client();
			Client(int socket);
			Client&	operator=(const Client& other);
			~Client();

			int		getSocket() const;
			std::string	getNick() const;
			std::string	getName() const;
			void	setNick(std::string nick);
			void	setUser(std::string user);

	private:
			int			_socket;
			std::string	_name;
			bool		_op;

			std::string _nick;
			std::string _user;
};


class	Channel
{
	public:
			Channel(char **argv);
			~Channel();

	private:
			std::string	_name;
			std::string	_password;
			std::string	_topic;
			

};

class	Server
{
	public:
			Server(char **argv);
			~Server();

			void	startServer();
			void	waitingClients();
			void	closeServer();

			std::string recData(Client *client);

			void	parseClient(Client *client);

	private:
			Client*				_clients[1024];
			Channel*			_channels[1024];

			unsigned int		_nbClient;
			unsigned int		_port;
			std::string			_password;
			int					_socket;
			struct sockaddr_in	_sockstruct;
			int					structSize;
};

int		parse(char *arg);

#endif
