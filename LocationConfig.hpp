/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationConfig.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 17:12:27 by aelkhali          #+#    #+#             */
/*   Updated: 2023/09/05 22:44:18 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATIONCONFIG_HPP
#define LOCATIONCONFIG_HPP

#include <string>
#include <vector>

class LocationConfig
{
public:

    /*  Constructors */
    LocationConfig();
    LocationConfig(const std::string& path);

    /*  Setters */
    void    setAlias(const std::string& alias);
    void    setRoot(const std::string& root);
    void    setAutoIndex( bool autoIndex );
    void    setIndex (std::string const& index );

    /*  Other Helper Functions  */
    void clear();

    /*  Getters */
    const std::vector<std::string>& getIndex() const;
    const std::string&              getAlias() const;
    const std::string&              getRoot() const;
    const std::string&              getPath() const;
    bool                            isEmpty() const;
    bool                            getAutoIndex() const;

private:
    std::string                 path;
    std::string                 alias;
    std::string                 root;
    bool                        autoIndex;
    std::vector<std::string>    index;
};

#endif
