/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationConfig.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 19:14:52 by aelkhali          #+#    #+#             */
/*   Updated: 2023/09/05 19:25:23 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LocationConfig.hpp"

// Constructor
LocationConfig::LocationConfig() : autoIndex(false) {}
LocationConfig::LocationConfig(const std::string& path) : path(path), autoIndex(false) {}

// Setters
void LocationConfig::setAlias(const std::string& alias) {
    this->alias = alias;
}
void LocationConfig::setRoot(const std::string& root) {
    this->root = root;
}
void LocationConfig::setAutoIndex(bool autoIndex) {
    this->autoIndex = autoIndex;
}
void LocationConfig::setIndex(const std::string& index)
{
    this->index.push_back(index);
}

// Clear the configuration
void LocationConfig::clear()
{
    alias.clear();
    root.clear();
    autoIndex = false;
    index.clear();
}

// Getters
const std::string&              LocationConfig::getAlias() const
{
    return alias;
}
bool                            LocationConfig::getAutoIndex() const
{
    return autoIndex;
}
const std::vector<std::string>& LocationConfig::getIndex() const
{
    return index;
}
bool                            LocationConfig::isEmpty() const
{
    if (alias.empty() || root.empty())
        return false;
    return true;
}
const std::string&              LocationConfig::getRoot() const
{
    return root;
}
const std::string&              LocationConfig::getPath() const
{
    return path;
}