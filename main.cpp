/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 18:09:50 by aelkhali          #+#    #+#             */
/*   Updated: 2023/09/03 20:59:52 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigFileParser.hpp"

int main(int ac, char *av[])
{
    if (ac != 2)
        return 1;
    std::string arg(av[1]);
    ConfigFileParser    configFile(arg);
    
    configFile.parseServersData();

    configFile.getServers()[0].printServerConfig();
    configFile.getServers()[1].printServerConfig();
    configFile.getServers()[2].printServerConfig();
    return 0;
}