/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationConfig.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 19:14:52 by aelkhali          #+#    #+#             */
/*   Updated: 2023/09/03 19:48:55 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LocationConfig.hpp"

// Constructor
LocationConfig::LocationConfig() : autoIndex(false) {}

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
const std::string& LocationConfig::getAlias() const
{
    return alias;
}

// Getter for AutoIndex
bool LocationConfig::getAutoIndex() const
{
    return autoIndex;
}

// Getter for Index
const std::vector<std::string>& LocationConfig::getIndex() const
{
    return index;
}

bool LocationConfig::isEmpty() const
{
    if (alias.empty() || root.empty())
        return false;
    return true;
}

const std::string& LocationConfig::getRoot() const
{
    return root;
}