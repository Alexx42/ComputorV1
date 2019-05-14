/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computorv1.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 10:54:03 by ale-goff          #+#    #+#             */
/*   Updated: 2019/05/13 21:37:57 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseExpression.hpp"

int         main(int ac, char **av) {
    if (ac != 2) {
        std::cout << "usage: ./ComputorV1 [expression]" << std::endl;
        return (1);
    }
    ParseExpression expr;
    try {
        expr = ParseExpression(av[1]);
        expr.acceptTerm();
    }catch (ParseExpression::BadExpression &e) {
        std::cout << e.what() << std::endl;
        return (1);
    }
    MapData<int, int>::iterator it = expr.getMapData().getMap()->begin();
    MapData<int, int>::iterator ite = expr.getMapData().getMap()->end();

    while (it != ite) {
        std::cout << "Number = " << it->second << std::endl;
        std::cout << "Exposant = " << it->first << std::endl;
        it++; 
    }
}