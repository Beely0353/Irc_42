/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biaroun <biaroun@student.42nice.fr> >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:17:06 by biaroun           #+#    #+#             */
/*   Updated: 2024/10/01 17:19:10 by biaroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main()
{
    std::string arg = "channel42 123";
    std::string channelName = arg.substr(0, arg.find(" "));
    std::string password = arg.substr(arg.find(" ") + 1);
    
    std::cout << arg << std::endl;
    std::cout << channelName << "lq" <<std::endl;
    std::cout << password << std::endl;
    return 0;
}
