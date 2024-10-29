/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:40:28 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/18 13:40:28 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Channel.hpp"

const std::string			&Channel::getName() {return this->_name;}
const std::string			&Channel::getPassword() {return this->_password;}
const std::string			&Channel::getTopic() {return this->_topic;}
const std::string			&Channel::getTopicUser() {return this->_topicUser;}
const std::string			&Channel::getTopicTime() {return this->_topicTime;}
const std::string			&Channel::getDate() {return this->_date;}
const bool					&Channel::getI() {return this->_i;}
const bool					&Channel::getT() {return this->_t;}
const bool					&Channel::getK() {return this->_k;}
const bool					&Channel::getL() {return this->_l;}
const unsigned int			&Channel::getMaxClient() {return this->_maxClient;}
std::vector<std::string>	&Channel::getInvited() {return this->_invited;}
std::map<std::string, bool>	&Channel::getMembers() {return this->_members;}
