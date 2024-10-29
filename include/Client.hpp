/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:08:09 by mgayout           #+#    #+#             */
/*   Updated: 2024/09/27 10:08:09 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "Server.hpp"

class	Client
{
	public:
			Client(int socket, struct sockaddr_in sockstruct);
			~Client();

			const int					&getSocket();
			const struct sockaddr_in	&getSockstruct();
			const std::string			&getNickname();
			const std::string			&getUsername();
			const bool					&getPwd();
			const bool					&getNick();
			const bool					&getUser();
			const bool					&getHexchat();
			bool					getAuthenticated();

			void						setNickname(const std::string nick);
			void						setUsername(const std::string user);
			void						setPwd(bool b);
			void						setNick(bool b);
			void						setUser(bool b);
			void						setHexchat(bool b);

			void	addChannel(std::string channel);

	private:
			int							_socket;
			struct sockaddr_in			_sockstruct;
			std::string					_nickname;
			std::string					_username;
			bool						_pwd;
			bool						_nick;
			bool						_user;
			bool						_hexchat;
			std::vector<std::string>	_channels;
};

#endif