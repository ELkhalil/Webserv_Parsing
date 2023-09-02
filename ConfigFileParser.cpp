/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigFileParser.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 18:13:37 by aelkhali          #+#    #+#             */
/*   Updated: 2023/09/01 18:26:30 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigFileParser.hpp"

void    ConfigFileParser::_configFileOpeningChecker()
{
    std::ifstream   configFile(this->_configFile);

    bool is_empty = configFile.peek() == std::ifstream::traits_type::eof();
    if (!configFile.is_open())
    {
        std::cerr << "Error: Failed to open " << std::endl;
        // some behaivior here 
        std::exit(1);
    }
    if (is_empty)
    {
        std::cerr << "Error: Empty File" << std::endl;
        std::cerr << "Try With Another File" << std::endl;
        std::exit(1);
    }
}