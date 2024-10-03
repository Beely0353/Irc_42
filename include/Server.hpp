/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 09:29:49 by mgayout           #+#    #+#             */
/*   Updated: 2024/09/27 09:29:49 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <algorithm>
# include <sys/socket.h>
# include <unistd.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <fcntl.h>
# include <poll.h>
# include <vector>
# include <map>
# include <stdlib.h>

# include "Client.hpp"
# include "Channel.hpp"

class Client;

class	Server
{
	public:
			Server(char **argv);
			~Server();

			int		getSocket();
			void	launching();
			void	addClient();
			void	clientRequest(unsigned int idClient);
			void	parseCommand(int clientFd, std::string line);

			void		pass(std::string arg, int clientFd);
			void		nick(std::string arg, int clientFd);
			void		user(std::string arg, int clientFd);
			void		oper(std::string arg, int clientFd);
			void		mode(std::string arg, int clientFd, std::string chanName)
			void		PrivateChannel(std::string arg, std::string chanName);
			void		quit(std::string arg, int clientFd);

			void		join(std::string arg, int clientFd);
			void		JoinPsswrd(std::string arg, int clientFd);
			void		joinDefault(std::string arg, int clientFd);

			void		part(std::string arg, int clientFd);
			void		topic(std::string arg, int clientFd);
			void		kick(std::string arg, int clientFd);
			void		privmsg(std::string arg, int clientFd);
			void		notice(std::string arg, int clientFd);
			void		sendfile(std::string arg, int clientFd);
			void		getfile(std::string arg, int clientFd);
			void		bot(std::string arg, int clientFd);
			void		cap(int clientFd);

			/*void	authentication();
			std::string	findNickname(char *buffer);
			std::string	findUsername(char *buffer);
			void	setNickClient(std::string nick);
			void	setUserClient(std::string user);

			int		nicknameUsed(std::string nick);
			int		usernameUsed(std::string user);*/

	private:
			unsigned int			_port;
			std::string				_password;
			unsigned int			_nbClient;
			unsigned int			_nbClientMax;
			struct pollfd*			_pfds;
			std::map<int, Client *>	_clients;
			int						_socket;
			
			std::map<string, Channel *>		_channels;
			unsigned int			_nbChannel;
};

void	sendMessage(int fd, std::string msg);
std::string trim(const std::string& str);
std::vector<std::string> split(const std::string& str, char delimiter);

#endif
