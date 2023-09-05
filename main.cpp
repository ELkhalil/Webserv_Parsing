/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 18:09:50 by aelkhali          #+#    #+#             */
/*   Updated: 2023/09/05 22:38:10 by aelkhali         ###   ########.fr       */
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

    for (int i = 0; i < (int)configFile.getServers().size(); i++)
    {
        configFile.getServers()[i].printServerConfig();
    }
    
    
    return 0;
}