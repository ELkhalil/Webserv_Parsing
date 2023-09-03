/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 14:28:35 by aelkhali          #+#    #+#             */
/*   Updated: 2023/09/03 20:20:29 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERCONFIG_HPP
#define SERVERCONFIG_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "LocationConfig.hpp"

class   ServerConfig
{
public:


    ServerConfig ( void );
    void    setListenPort(int ports);
    void    addServerName(const std::string& serverName);
    void    setLocation(LocationConfig const& locationObj);
    void    setDefaultServer(bool isDefault);
    void    addErrorPage(int errorCode, const std::string& errorPage);
    void    setMaxBodySize(int sizeInBytes);
    void    addRoute(const std::string& route, const std::string& config);

    const   std::vector<int>& getListenPorts() const;
    const std::vector<std::string>& getServerNames() const;
    const std::vector<LocationConfig>& getLocations() const;
    bool    isDefaultServer() const;
    const std::map<int, std::string>& getErrorPages() const;
    int getMaxBodySize() const;
    const std::map<std::string, std::string>& getRoutes() const;
    void printServerConfig() const;

private:
    std::vector<int>                    _listenPort;
    std::vector<std::string>            _serverNames;
    bool                                _isDefaultServer;
    std::map<int, std::string>          _errorPages;
    int                                 _maxBodySize;
    std::map<std::string, std::string>  _routes;
    std::vector<LocationConfig>         _locations;
};
#endif
