/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigFileParser.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 18:13:37 by aelkhali          #+#    #+#             */
/*   Updated: 2023/09/03 20:58:29 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigFileParser.hpp"

/*  ConfigFile Constructors  */
ConfigFileParser::ConfigFileParser(const std::string &fileName) : _configFileName(fileName)
{
}

void ConfigFileParser::parseServersData()
{
    std::vector<LocationConfig> locations;
    std::string line;
    bool serverEnded = false;
    ServerConfig currentConfig;

    std::ifstream _configFile(_configFileName.c_str());

    if (!_configFile.is_open())
        _errorAndExit("Error: Failed to open Config File");
    bool is_empty = _configFile.peek() == std::ifstream::traits_type::eof();
    if (is_empty)
        _errorAndExit("Error: Empty Config File");

    while (getline(_configFile, line))
    {
        std::cout << line << std::endl;
        if (_configFile.fail())
            _errorAndExit("Error: While Reading Config File...");
        if (line.empty() && _configFile.eof())
        {
            if (_servers.empty())
                _errorAndExit("Error: A file Must have at least one server");
            break;
        }
        std::string trimmedLine = _removeExtraSpaces(line);
        if (_isLineEmptyOrComment(trimmedLine))
            continue;
        if (!trimmedLine.empty() && trimmedLine == "server")
        {
            currentConfig = ServerConfig();
            getline(_configFile, line);
            if (_configFile.fail() && !_configFile.eof())
                _errorAndExit("Error: While Reading Config File...");
            if (_removeExtraSpaces(line) != "{")
                 _errorAndExit("Error: A Server Block Must be followed by : { ");
            while (getline(_configFile, line))
            {
                if (_configFile.fail() && !_configFile.eof())
                    _errorAndExit("Error: While Reading Config File...");
                std::string trimmedLine = _removeExtraSpaces(line);
                if (_isLineEmptyOrComment(line))
                    continue;
                
                /*  PARSING DIRECTIVES */
                std::istringstream iss(trimmedLine);
                std::vector<std::string> tokens;
                std::string token;

                while (iss >> token)
                    tokens.push_back(token);

                if (tokens.empty())
                    _errorAndExit("A Config File Must Contain Directives.");

                if (line.find("location") != std::string::npos)
                {
                    std::string path;

                    if (tokens[0] != "location")
                        _errorAndExit("Error: 'location' directive keyword must start with 'location'.");
                    if (tokens.size() < 3)
                        _errorAndExit("Error: 'location' directive must have at a single path as argument");
                    if (tokens.back() != "{")
                        _errorAndExit("Error: 'location' directive must end with '{'.");
                    path = tokens[1];

                    LocationConfig currentLocationConfig;

                    while (getline(_configFile, line))
                    {
                        if (_configFile.fail() && !_configFile.eof())
                            _errorAndExit("Error: While Reading Config File...");
                        std::string trimmedLine = _removeExtraSpaces(line);
                        if (_isLineEmptyOrComment(line))
                            continue;
                        if (trimmedLine == "}")
                        {
                            if (currentLocationConfig.isEmpty())
                                _errorAndExit("Location Section Must not be empty !");
                            currentConfig.setLocation(currentLocationConfig);
                            break;
                        }
                        _parseLocation(trimmedLine, currentLocationConfig);
                    }
                    continue;
                }
                else if (tokens[0] == "listen")
                {
                    if (tokens.size() != 2)
                        _errorAndExit("'listen' directive must have a single port to listen to.");
                    if (!_isLineEndsWithSemicolone(trimmedLine))
                        _errorAndExit("Missing semicolon at the end of the 'listen' directive.");
                    std::vector<std::string> listenTokens = _splitBySemicolon(tokens.back());
                    if (listenTokens.size() > 1)
                        _errorAndExit("Duplicate semicolons in the 'listen' directive.");
                    if (!tokens[tokens.size() - 1].empty())
                        tokens[tokens.size() - 1].erase(tokens[tokens.size() - 1].size() - 1);
                    currentConfig.setListenPort(_stringToInt(tokens[1]));
                }
                else if (tokens[0] == "server_name")
                {
                    if (tokens.size() <= 1)
                        _errorAndExit("'server_name' directive must have a single argument.");
                    if (!_isLineEndsWithSemicolone(trimmedLine))
                        _errorAndExit("Missing semicolon at the end of the 'server_name' directive.");
                    std::vector<std::string> servNamesTokens = _splitBySemicolon(tokens.back());
                    if (servNamesTokens.size() > 1)
                        _errorAndExit("Duplicate semicolons in the 'server_name' directive.");
                    if (!tokens[tokens.size() - 1].empty())
                        tokens[tokens.size() - 1].erase(tokens[tokens.size() - 1].size() - 1);
                    for (int i = 1; i < (int)tokens.size(); i++)
                        currentConfig.addServerName(tokens[i]);
                }
                else if (tokens[0] == "default_server")
                {
                    if (tokens.size() != 2)
                        _errorAndExit("'default_server' directive must have a single argument: on or off");
                    if (!_isLineEndsWithSemicolone(trimmedLine))
                        _errorAndExit("Missing semicolon at the end of the 'default_server' directive.");
                    std::vector<std::string> listenTokens = _splitBySemicolon(tokens.back());
                    if (listenTokens.size() > 1)
                        _errorAndExit("Duplicate semicolons in the 'default_server' directive.");
                    if (!tokens[tokens.size() - 1].empty())
                        tokens[tokens.size() - 1].erase(tokens[tokens.size() - 1].size() - 1);
                    if (tokens[1] == "on")
                        currentConfig.setDefaultServer(true);
                    else if (tokens[1] == "off")
                        currentConfig.setDefaultServer(false);
                    else
                        _errorAndExit("cannot recognize the 'default_server' directive Arguments try {on || off}.");
                }
                else if (tokens[0] == "error_page")
                {
                    if (tokens.size() != 3)
                        _errorAndExit("'error_page' directive must have two argument: error and errorPage");
                    if (!_isLineEndsWithSemicolone(trimmedLine))
                        _errorAndExit("Missing semicolon at the end of the 'error_page' directive.");
                    std::vector<std::string> listenTokens = _splitBySemicolon(tokens.back());
                    if (listenTokens.size() > 1)
                        _errorAndExit("Duplicate semicolons in the 'error_page' directive.");
                    if (!tokens[tokens.size() - 1].empty())
                        tokens[tokens.size() - 1].erase(tokens[tokens.size() - 1].size() - 1);
                    currentConfig.addErrorPage(_stringToInt(tokens[1]), tokens[2]);
                }
                else if (tokens[0] == "root")
                {
                    if (tokens.size() != 2)
                        _errorAndExit("'root' directive must have One argument: Path");
                    if (!_isLineEndsWithSemicolone(trimmedLine))
                        _errorAndExit("Missing semicolon at the end of the 'root' directive.");
                    std::vector<std::string> listenTokens = _splitBySemicolon(tokens.back());
                    if (!tokens[tokens.size() - 1].empty())
                        tokens[tokens.size() - 1].erase(tokens[tokens.size() - 1].size() - 1);
                    if (listenTokens.size() > 1)
                        _errorAndExit("Duplicate semicolons in the 'root' directive.");
                }
                if (tokens[0] == "}")
                {
                    _servers.push_back(currentConfig);
                    serverEnded = true;
                    continue;
                }
            }
            if (!serverEnded)
                _errorAndExit("Unable to find the closing bracket for the server : }");
        }
        else
            _errorAndExit("Error: A config File Must start with : <server> without <>");
    }
    _configFile.close();
}

/* ######################## Parsing Helper Functions ########################### */
bool ConfigFileParser::_isLineEmptyOrComment(std::string const &line)
{
    if (line.empty() || line[0] == '#' || line[0] == '\n')
        return true;
    return false;
}
/*  Iterate and remove Extra Spaces from a line */
std::string ConfigFileParser::_removeExtraSpaces(const std::string &line)
{
    std::string result;
    bool spaceFound = false;

    if (line.empty())
        return line;
    for (size_t i = 0; i < line.length(); ++i)
    {
        if (line[i] == ' ' || line[i] == '\t')
            spaceFound = true;
        else
        {
            if (spaceFound)
            {
                result += ' ';
                spaceFound = false;
            }
            result += line[i];
        }
    }

    if (result.empty())
        return result;
    result = result.substr(result.find_first_not_of(" "));
    result = result.substr(0, result.find_last_not_of(" ") + 1);

    return result;
}
/*  Error printer and exit handler */
void ConfigFileParser::_errorAndExit(std::string const &error)
{
    std::cerr << error << std::endl;
    _exit(1);
}

bool ConfigFileParser::_isLineEndsWithSemicolone(const std::string &str)
{
    if (!str.empty() && str[str.length() - 1] == ';')
        return true;
    return false;
}

std::vector<std::string> ConfigFileParser::_splitBySemicolon(const std::string &str)
{
    std::vector<std::string> tokens;
    std::istringstream iss(str);
    std::string token;
    while (std::getline(iss, token, ';'))
    {
        if (!token.empty())
            tokens.push_back(token);
    }
    return tokens;
}

int ConfigFileParser::_stringToInt(const std::string &input)
{
    std::istringstream iss(input);
    long value;

    iss >> value;

    if (iss.fail() || !iss.eof())
        _errorAndExit("Port: Invalid characters in Port Value");
    if (value < 1 || value > 65535)
        _errorAndExit("Port: Out Of Range Port Value");
    int result = static_cast<int>(value);
    return result;
}

void ConfigFileParser::_parseLocation(std::string &trimmedLine, LocationConfig &currentLocationConfig)
{

    std::istringstream iss(trimmedLine);
    std::vector<std::string> tokens;
    std::string token;

    while (iss >> token)
        tokens.push_back(token);

    if (tokens.empty())
        _errorAndExit("A Location Section Must Contain Directives.");
    if (tokens[0] == "root")
    {
        if (tokens.size() != 2)
            _errorAndExit("'root' directive must have a single path.");
        if (!_isLineEndsWithSemicolone(trimmedLine))
            _errorAndExit("Missing semicolon at the end of the 'root' directive.");
        std::vector<std::string> locationTokens = _splitBySemicolon(tokens.back());
        if (locationTokens.size() > 1)
            _errorAndExit("Duplicate semicolons in the 'root' directive inside location.");
        currentLocationConfig.setRoot(tokens[1]);
    }
    else if (tokens[0] == "alias")
    {
        if (tokens.size() != 2)
            _errorAndExit("'alias' directive must have a single argument.");
        if (!_isLineEndsWithSemicolone(trimmedLine))
            _errorAndExit("Missing semicolon at the end of the 'alias' directive.");
        std::vector<std::string> locationTokens = _splitBySemicolon(tokens.back());
        if (locationTokens.size() > 1)
            _errorAndExit("Duplicate semicolons in the 'alias' directive inside location.");
        currentLocationConfig.setAlias(tokens[1]);
    }
    else if (tokens[0] == "autoindex")
    {
        if (tokens.size() != 2)
            _errorAndExit("'autoindex' directive must have a single argument: on or off");
        if (!_isLineEndsWithSemicolone(trimmedLine))
            _errorAndExit("Missing semicolon at the end of the 'autoindex' directive.");
        std::vector<std::string> listenTokens = _splitBySemicolon(tokens.back());
        if (listenTokens.size() > 1)
            _errorAndExit("Duplicate semicolons in the 'autoindex' directive.");
        if (!tokens[tokens.size() - 1].empty())
            tokens[tokens.size() - 1].erase(tokens[tokens.size() - 1].size() - 1);
        if (tokens[1] == "on")
            currentLocationConfig.setAutoIndex(true);
        else if (tokens[1] == "off")
            currentLocationConfig.setAutoIndex(false);
        else
            _errorAndExit("cannot recognize the 'autoindex' directive Arguments try {on || off}.");
    }
    else if (tokens[0] == "index")
    {
        if (tokens.size() < 2)
            _errorAndExit("'index' directive must have arguments");
        if (!_isLineEndsWithSemicolone(trimmedLine))
            _errorAndExit("Missing semicolon at the end of the 'index' directive.");
        std::vector<std::string> listenTokens = _splitBySemicolon(tokens.back());
        if (listenTokens.size() > 1)
            _errorAndExit("Duplicate semicolons in the 'index' directive.");
        for (int i = 1; i < (int)tokens.size(); i++)
            currentLocationConfig.setIndex(tokens[i]);
    }
}


std::vector<ServerConfig>   ConfigFileParser::getServers( void ) const
{
    return _servers;
}