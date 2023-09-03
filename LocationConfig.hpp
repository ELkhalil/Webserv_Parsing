/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationConfig.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 17:12:27 by aelkhali          #+#    #+#             */
/*   Updated: 2023/09/03 19:34:24 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATIONCONFIG_HPP
#define LOCATIONCONFIG_HPP

#include <string>
#include <vector>

// Custom struct to represent redirection configuration
class LocationConfig {
public:
    LocationConfig();

    void setAlias(const std::string& alias);
    void setRoot(const std::string& root);
    void setAutoIndex( bool autoIndex );
    void setIndex (std::string const& index );

    void clear();

    const std::string& getAlias() const;
    const std::string& getRoot() const;
    bool isEmpty() const;

    bool getAutoIndex() const;
    const std::vector<std::string>& getIndex() const;



private:
    std::string                 alias;
    std::string                 root;
    bool                        autoIndex;
    std::vector<std::string>    index;
};

#endif
