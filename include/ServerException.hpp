/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerException.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:37:37 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/16 13:37:37 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVEREXCEPTION_HPP
# define SERVEREXCEPTION_HPP

# include "Utils.hpp"

class SocketCreationError : public std::exception {
public:
	virtual const char *what() const throw();
};
class SocketBindError : public std::exception {
public:
	virtual const char *what() const throw();
};
class SocketListenError : public std::exception {
public:
	virtual const char *what() const throw();
};
class RecvError : public std::exception {
public:
	virtual const char *what() const throw();
};
class sendException : public std::exception {
public:
	virtual const char *what() const throw();
};
class pollException : public std::exception {
public:
	virtual const char *what() const throw();
};

#endif