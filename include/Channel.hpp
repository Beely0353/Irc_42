/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biaroun <biaroun@student.42nice.fr> >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:13:42 by biaroun           #+#    #+#             */
/*   Updated: 2024/10/03 13:11:27 by biaroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Client.hpp"
#include "Server.hpp"

# define OP "OP"
# define USER "USER"

class	Channel
{
	public:
			Channel(Client *fonda, std::string name, std::string password);
			~Channel();

			void	addMember(Client *client, std::string password)
			void	removeMember(Client *client);
            bool    isOP(Client *client);
            
			void	setTopic(std::string topic);
			void	setPassword(std::string password);
            void    setPrivate(bool priv);
            
            bool    getPrivate();

			void	SendMessChanALL(std::string msg, std::string chanName)
			void	SendMessChan(std::string msg, std::string chanName, Client *send)

	private:
			std::string	_name;
			std::string	_password;
			std::string	_topic;
            bool        _private;
            size_t      _maxClients;

			std::map<Client*, std::string> _members;
};
