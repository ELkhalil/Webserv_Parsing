/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 19:18:06 by aelkhali          #+#    #+#             */
/*   Updated: 2023/09/03 20:25:06 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerConfig.hpp"

// Constructor
ServerConfig::ServerConfig() : _isDefaultServer(false), _maxBodySize(0) {}

// Setters
void ServerConfig::setListenPort(int port) {
    _listenPort.push_back(port);
}

void ServerConfig::addServerName(const std::string& serverName) {
    _serverNames.push_back(serverName);
}

void ServerConfig::setLocation(LocationConfig const& locationObj) {
    _locations.push_back(locationObj);
}

void ServerConfig::setDefaultServer(bool isDefault) {
    _isDefaultServer = isDefault;
}

void ServerConfig::addErrorPage(int errorCode, const std::string& errorPage) {
    _errorPages[errorCode] = errorPage;
}

void ServerConfig::setMaxBodySize(int sizeInBytes) {
    _maxBodySize = sizeInBytes;
}

void ServerConfig::addRoute(const std::string& route, const std::string& config) {
    _routes[route] = config;
}

// Getters
const std::vector<int>& ServerConfig::getListenPorts() const
{
    return _listenPort;
}

const std::vector<std::string>& ServerConfig::getServerNames() const {
    return _serverNames;
}

const std::vector<LocationConfig>& ServerConfig::getLocations() const {
    return _locations;
}

bool ServerConfig::isDefaultServer() const {
    return _isDefaultServer;
}

const std::map<int, std::string>& ServerConfig::getErrorPages() const {
    return _errorPages;
}

int ServerConfig::getMaxBodySize() const {
    return _maxBodySize;
}

const std::map<std::string, std::string>& ServerConfig::getRoutes() const {
    return _routes;
}

void ServerConfig::printServerConfig() const
{
    std::cout << "Listen Ports:";
    for (size_t i = 0; i < _listenPort.size(); ++i)
    {
        std::cout << " " << _listenPort[i];
    }
    std::cout << std::endl;

    std::cout << "Server Names:";
    for (size_t i = 0; i < _serverNames.size(); ++i)
    {
        std::cout << " " << _serverNames[i];
    }
    std::cout << std::endl;

    std::cout << "Default Server: " << (_isDefaultServer ? "true" : "false") << std::endl;

    std::cout << "Error Pages:" << std::endl;
    for (std::map<int, std::string>::const_iterator it = _errorPages.begin(); it != _errorPages.end(); ++it)
    {
        std::cout << "  " << it->first << " => " << it->second << std::endl;
    }

    std::cout << "Max Body Size: " << _maxBodySize << " bytes" << std::endl;

    std::cout << "Routes:" << std::endl;
    for (std::map<std::string, std::string>::const_iterator it = _routes.begin(); it != _routes.end(); ++it)
    {
        std::cout << "  " << it->first << " => " << it->second << std::endl;
    }

    std::cout << "Locations:" << std::endl;
    for (size_t i = 0; i < _locations.size(); ++i)
    {
        std::cout << "Location " << i + 1 << ":" << std::endl;
        std::cout << "  Alias: " << _locations[i].getAlias() << std::endl;
        std::cout << "  Root: " << _locations[i].getRoot() << std::endl;
        std::cout << "  AutoIndex: " << (_locations[i].getAutoIndex() ? "true" : "false") << std::endl;
        std::cout << "  Index:";
        const std::vector<std::string>& locationIndex = _locations[i].getIndex();
        for (size_t j = 0; j < locationIndex.size(); ++j)
        {
            std::cout << " " << locationIndex[j];
        }
        std::cout << std::endl;
    }
}
