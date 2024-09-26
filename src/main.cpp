/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 08:08:07 by mgayout           #+#    #+#             */
/*   Updated: 2024/09/25 12:39:54 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_irc.hpp"

int	main(int argc, char **argv)
{
	if (argc != 3 || parse(argv[1]) || !argv[2])
	{
		std::cout << "Error: bad input" << std::endl;
		return 1;
	}
	Server	serv(argv);

	serv.startServer();
	serv.waitingClients();
	serv.closeServer();

	return 0;
}

int	parse(char *arg)
{
	std::string	port = arg;
	long long	nb;

	for (size_t i = 0; i != port.size(); i++)
	{
		if (!isdigit(port[i]))
			return 1;
	}
	nb = std::strtoll(arg, NULL, 10);
	if (nb > 2147483647)
		return 1;
	return 0;
}
