/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 14:28:35 by aelkhali          #+#    #+#             */
/*   Updated: 2023/09/05 22:44:48 by aelkhali         ###   ########.fr       */
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

    /*  Constructors */
    ServerConfig ( void );

    /* Add to vectors */
    void    addServerName(const std::string& serverName);
    void    addErrorPage(int errorCode, const std::string& errorPage);
    void    addLocation(LocationConfig const& locationObj);

    /*  Setters */
    void    setListenPort(int ports);
    void    setDefaultServer(bool isDefault);
    void    setMaxBodySize(int sizeInBytes);

    /*  Getters */
    const   std::vector<int>&                   getListenPorts() const;
    const   std::vector<std::string>&           getServerNames() const;
    const   std::vector<LocationConfig>&        getLocations() const;
    const std::map<int, std::string>&           getErrorPages() const;
    int                                         getMaxBodySize() const;
    // const std::map<std::string, std::string>&   getRoutes() const;
    bool                                        isDefaultServer() const;

    /*  Other Helper Functions  */
    void printServerConfig() const;

private:

    int                                 _maxBodySize;
    bool                                _isDefaultServer;
    std::vector<int>                    _listenPort;
    std::vector<std::string>            _serverNames;
    std::map<int, std::string>          _errorPages;
    std::vector<LocationConfig>         _locations;
    
};
#endif
