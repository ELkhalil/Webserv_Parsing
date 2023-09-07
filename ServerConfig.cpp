/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 19:18:06 by aelkhali          #+#    #+#             */
/*   Updated: 2023/09/07 21:16:08 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerConfig.hpp"

// Constructor
ServerConfig::ServerConfig() : _maxBodySize(0), _isDefaultServer(false) {}

// Setters
void ServerConfig::setListenPort(int port)
{
    this->_port = port;
}

void ServerConfig::setHost(std::string const& host)
{
    this->_host = host;
}

void ServerConfig::setServerName(std::string const& serverName)
{
    _serverName = serverName;
}

void ServerConfig::addLocation(LocationConfig const& locationObj)
{
    _locations.push_back(locationObj);
}
void ServerConfig::setDefaultServer(bool isDefault)
{
    _isDefaultServer = isDefault;
}

void ServerConfig::addErrorPage(int errorCode, const std::string& errorPage) 
{
    _errorPages[errorCode] = errorPage;
}
void ServerConfig::setMaxBodySize(int sizeInBytes)
{
    _maxBodySize = sizeInBytes;
}

// Getters
int ServerConfig::getListenPort() const
{
    return _port;
}
std::string     ServerConfig::getServerName() const 
{
    return _serverName;
}
const   std::vector<LocationConfig>&  ServerConfig::getLocations() const {
    return _locations;
}
bool    ServerConfig::isDefaultServer() const 
{
    return _isDefaultServer;
}
const   std::map<int, std::string>& ServerConfig::getErrorPages() const 
{
    return _errorPages;
}
int     ServerConfig::getMaxBodySize() const
{
    return _maxBodySize;
}


void ServerConfig::printServerConfig() const
{
    std::cout << "Listen Ports:";
    std::cout << " " << _port;
    
    std::cout << std::endl;

    std::cout << "Server Names:";
    std::cout << " " << _serverName;
    
    std::cout << std::endl;

    std::cout << "Default Server: " << (_isDefaultServer ? "true" : "false") << std::endl;

    std::cout << "Error Pages:" << std::endl;
    for (std::map<int, std::string>::const_iterator it = _errorPages.begin(); it != _errorPages.end(); ++it)
    {
        std::cout << "  " << it->first << " => " << it->second << std::endl;
    }

    std::cout << "Max Body Size: " << _maxBodySize << " bytes" << std::endl;

    // std::cout << "Routes:" << std::endl;
    // for (std::map<std::string, std::string>::const_iterator it = _routes.begin(); it != _routes.end(); ++it)
    // {
    //     std::cout << "  " << it->first << " => " << it->second << std::endl;
    // }

    std::cout << "Locations:" << std::endl;
    for (size_t i = 0; i < _locations.size(); ++i)
    {
        std::cout << "Location " << i + 1 << ":" << std::endl;
        std::cout << "  Root: " << _locations[i].getRoot() << std::endl;
        std::cout << "  AutoIndex: " << (_locations[i].getAutoIndex() ? "true" : "false") << std::endl;
        std::cout << "  Index:";
        const std::vector<std::string>& locationIndex = _locations[i].getIndexes();
        for (size_t j = 0; j < locationIndex.size(); ++j)
        {
            std::cout << " " << locationIndex[j];
        }
        std::cout << std::endl;
    }
}
