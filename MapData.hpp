/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapData.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 19:42:26 by ale-goff          #+#    #+#             */
/*   Updated: 2019/05/15 00:07:57 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPDATA_HPP
# define MAPDATA_HPP

#include <map>
#include <iterator>
template <typename T, typename V>
class MapData {
    public:
    typedef typename std::map<T, V>::iterator iterator;
        MapData<T, V>( void ) {_mapData = new std::map<T, V>[1];}
        ~MapData<T, V>( void ) {delete [] _mapData;}

        void        myInsert( T key, V val) {
            V tmp;
            if (_mapData->find(key) != _mapData->end()) {
                tmp = _mapData->find(key)->second;
                _mapData->erase(_mapData->find(key));
                val = val + tmp;
            }
            if (val != 0)
                _mapData->insert(std::pair<T, V>(key, val));

        }
    std::map<T, V> * getMap( void )const {
        return this->_mapData;
    }
    private:
        std::map <T, V> *_mapData;
};

# endif