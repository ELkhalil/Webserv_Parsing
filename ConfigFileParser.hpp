/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigFileParser.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 17:54:08 by aelkhali          #+#    #+#             */
/*   Updated: 2023/09/01 18:28:09 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGFILEPARSER_HPP
#define CONFIGFILEPARSER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

struct Directive
{
    std::string             dirName;
    std::string             dirArguments;
};

struct Block 
{
    std::string             blockName;
    std::vector<Directive>  directives;
    std::vector<Block>      nestedBlocks;
};

class ConfigFileParser {
public:
    ConfigFileParser(const std::string& fileName);
    // Add functions to parse and process the configuration file here
private:
    std::string             _configFile;
    std::vector<Block>      _blocks;
    void                    _configFileOpeningChecker();
};

#endif
