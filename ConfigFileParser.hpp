/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigFileParser.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 17:54:08 by aelkhali          #+#    #+#             */
/*   Updated: 2023/09/03 20:43:25 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGFILEPARSER_HPP
#define CONFIGFILEPARSER_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <sstream>
#include <limits>
#include "ServerConfig.hpp"
#include "LocationConfig.hpp"
/*
    // do not FIRGET to close the file
*/
class ConfigFileParser
{
public:
    ConfigFileParser(const std::string &fileName);
    void parseServersData();
    std::vector<ServerConfig>   getServers( void ) const;
private:

    std::string                 _configFileName;
    std::ifstream               _configFile;
    std::vector<ServerConfig>   _servers;

    std::string _removeExtraSpaces(std::string const &line);
    void _errorAndExit(std::string const &error);
    bool _isLineEmptyOrComment(std::string const &line );
    bool _isLineEndsWithSemicolone(const std::string &str);
    std::vector<std::string> _splitBySemicolon(const std::string &str);
    int _stringToInt(const std::string &input);
    void _parseLocation(std::string &trimmedLine, LocationConfig &currentLocationConfig);
    
    
};
#endif
