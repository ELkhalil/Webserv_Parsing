/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationConfig.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 19:14:52 by aelkhali          #+#    #+#             */
/*   Updated: 2023/09/08 19:40:54 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LocationConfig.hpp"

// LocationConfig Constructor
LocationConfig::LocationConfig() : _autoIndex(false) {}
LocationConfig::LocationConfig(const std::string& path) : _path(path), _autoIndex(false), _autoUpload(false) {}

// LocationConfig Setters
void LocationConfig::setRoot(const std::string& root)
{
    this->_root = root;
}
void LocationConfig::setUploadPath(const std::string& uploadPath)
{
    this->_uploadPath = uploadPath;
}
void LocationConfig::setCgiPath(const std::string& cgiPath)
{
    this->_cgiPath = cgiPath;
}
void LocationConfig::setAutoIndex(bool autoIndex)
{
    this->_autoIndex = autoIndex;
}
void LocationConfig::setAutoUpload(bool autoUpload)
{
    this->_autoUpload = autoUpload;
}

void LocationConfig::setIndex(const std::string& index)
{
    this->_indexes.push_back(index);
}

void LocationConfig::setAllowedMethod(const std::string& method)
{
    this->_allowedMethods.push_back(method);
}

// LocationConfig Getters
bool    LocationConfig::getAutoIndex() const
{
    return _autoIndex;
}

bool    LocationConfig::getAutoUpload() const
{
    return _autoUpload;
}

std::vector<std::string> LocationConfig::getIndexes() const
{
    return _indexes;
}
std::vector<std::string> LocationConfig::getAllowedMethods() const
{
    return _allowedMethods;
}

bool    LocationConfig::isEmpty() const
{
    if (_root.empty() && _indexes.size() < 1)
        return true;
    return false;
}
std::string LocationConfig::getRoot() const
{
    return _root;
}
std::string LocationConfig::getPath() const
{
    return _path;
}
std::string LocationConfig::getUploadPath() const
{
    return _uploadPath;
}
std::string LocationConfig::getCgiPath() const
{
    return _cgiPath;
}

bool    LocationConfig::isLocationValidAndReady( void )
{
    if (_path.empty() || _root.empty() || !_indexes.size() || !_allowedMethods.size())
        return false;
    return true;
}
