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
			Client(int socket);
			~Client();

			void		setNickname(const std::string nick);
			void		setUsername(const std::string user);
			void		setAuthenticated(bool b);
			void		setHexchat(bool b);
			void		setNickname(const std::string nick);
			void		setUsername(const std::string user);
			std::string	getNickname();
			std::string	getUsername();
			int			getSocket();
			bool		getHexchat();

	private:
			int			_socket;
			std::string	_nickname;
			std::string	_username;
			bool		_authenticated;
			bool		_hexchat;
};

#endif
