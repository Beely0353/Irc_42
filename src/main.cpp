/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 08:08:07 by mgayout           #+#    #+#             */
/*   Updated: 2024/09/27 10:37:59 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

int		parse(char *arg);

int	main(int argc, char **argv)
{
	if (argc != 3 || parse(argv[1]) || !argv[2])
	{
		std::cout << "Error: bad input" << std::endl;
		return 1;
	}
	Server	server(argv);

	try
	{
		server.launching();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

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
