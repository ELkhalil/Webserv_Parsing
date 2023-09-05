/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigFileParser.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 17:54:08 by aelkhali          #+#    #+#             */
/*   Updated: 2023/09/05 21:06:48 by aelkhali         ###   ########.fr       */
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
#include <stack>
#include "ServerConfig.hpp"
#include "LocationConfig.hpp"

/*  General Syntax Errors   */
#define READINGERROR "Error: While Reading Config File..."
#define BRACESERROR "Mismatched braces '{}' found."
#define FILEWITHOUTSERVER "Error: A config File Must start with a <server> without <>"

/*  Server Syntax Errors   */
#define READINSERVERGERROR "Error: While Reading Server Section..."
#define SERVERNOTFOUNDERROR "Error: A file Must have at least one server"
#define SERVERSYNTAXERROR "Error: A Server Block Must be followed by : {"
#define SECTIONSYNTAXERROR "A Section of a Config File Must Contain Directives."
#define SERVERBRACEERROR "Unable to find the closing brace for the server : }"

/*  Location Syntax Errors */
#define LOCATIONNOTFOUNDERROR "Error: 'location' directive keyword must start with 'location'."
#define LOCATIONSIZEERROR "Error: 'location' directive must have a single path as argument and {"
#define LOCATIONSYNTAXERROR "Error: 'location' directive must end with '{'"
#define SECTIONSYNTAXERROR "A Section of a Config File Must Contain Directives."
#define READINLOCATIONERROR "Error: While Reading Location Section..."

class ConfigFileParser
{
public:

    /*  ConfigFileParser Constructors */
    ConfigFileParser(const std::string &fileName);
    ~ConfigFileParser( void );

    /*  ConfigFileParser Member Functions */
    void parseServersData();
    /*  ConfigFileParser Getters */
    std::vector<ServerConfig>   getServers( void ) const;

private:

    std::string                 _configFileName;
    std::ifstream               _configFile;
    std::vector<ServerConfig>   _servers;

    /*  Parsing Data Functions  */
    void    _parseLocationDirectives(std::string &trimmedLine, LocationConfig &currentLocationConfig);
    
    /*  Error Displayer with Exit */
    void    _errorAndExit(std::string const &error);

    /*  Parsing Helper Functions */
    void                     _splitBySemicolon( std::string const& );
    std::string              _removeExtraSpaces(std::string  const& );
    bool                     _isLineEmptyOrComment(std::string  const& );
    int                      _stringToInt( std::string const& );
    int                      _stringToIntPort( std::string const& );

    /*  FileStream Releted Functions  */
    void                     _isFileOpenedAndNotEmpty( std::ifstream& );
    bool                     _isFileGoodToGo( std::string const& );
    
    /*  Parsing Directives Functions */
    std::vector<std::string> _tokenizerOfDirectives( std::string const& );

};
#endif
