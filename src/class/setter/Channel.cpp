/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:41:15 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/18 16:41:15 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Channel.hpp"

void	Channel::setTopic(std::string topic) {this->_topic = topic;}
void	Channel::setI(bool i) {this->_i = i;}
void	Channel::setT(bool t) {this->_t = t;}
void	Channel::setK(bool k) {this->_k = k;}
void	Channel::setL(bool l) {this->_l = l;}
void	Channel::setMaxClient(unsigned int max) {this->_maxClient = max;}