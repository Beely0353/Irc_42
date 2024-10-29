/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biaroun <biaroun@student.42nice.fr> >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:13:42 by biaroun           #+#    #+#             */
/*   Updated: 2024/10/29 17:00:00 by biaroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Client.hpp"
# include "Server.hpp"

class Client;

class	Channel
{
	public:
			Channel(Client *fonda, std::string name, std::string password);
			~Channel();

			const std::string			&getName();
			const std::string			&getPassword();
			const std::string			&getTopic();
			const std::string			&getTopicUser();
			const std::string			&getTopicTime();
			const std::string			&getDate();
			const bool					&getI();
			const bool					&getT();
			const bool					&getK();
			const bool					&getL();
			const unsigned int			&getMaxClient();
			std::vector<std::string>	&getInvited();
			std::map<std::string, bool>	&getMembers();

			void	setTopic(std::string topic);
			void	setI(bool i);
			void	setT(bool t);
			void	setK(bool k);
			void	setL(bool l);
			void    setPrivate(bool priv);
			void	setPassword(std::string password);
			void	setTopicChange(bool change);
			void	setMaxClient(unsigned int max);

			void	OP(std::string client);
			void	DEOP(std::string client);

			bool	isInvited(std::string username);
			bool	isMember(std::string client);
			bool    isOP(std::string client);
			bool	isTopicProtected();

			void	addClient(std::string username);
			void	addInvited(std::string client);
			Client  *findClientChannel(std::string Username);

			int		removeMember(Client* client);

	private:
			std::string						_name;
			std::string						_password;
			std::string						_topic;
			std::string						_topicUser;
			std::string						_topicTime;
			std::string						_date;
            bool        					_i;
			bool							_t;
			bool							_k;
			bool							_l;
			bool							_private;
			bool							_topicChange;
            unsigned int					_maxClient;
			std::vector<std::string>		_invited;
			std::map<std::string, bool>		_members;
};

#endif
