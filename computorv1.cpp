/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computorv1.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alex <Alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 10:54:03 by ale-goff          #+#    #+#             */
/*   Updated: 2019/05/14 01:29:52 by Alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseExpression.hpp"
#include <cmath>

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
	std::cout << "Refactored expression: ";
    while (it != ite) {
			if (it->second > 0 && it != expr.getMapData().getMap()->begin()) {
			std::cout << "+ ";
		}
		std::cout << it->second;
	
		if (it->first != 0) {
			std::cout << "x^" << it->first;
		}
		std::cout << " ";
//        std::cout << "Number = " << it->second << std::endl;
  //      std::cout << "Exposant = " << it->first << std::endl;
        it++; 
    }
//	std::cout << "= 0";
	//int		a = expr.getMapData().getMap()->at(0);
	//int		b = expr.getMapData().getMap()->at(1);
	//int		c = expr.getMapData().getMap()->at(2);
//	std::cout << std::endl;
//	std::cout << "Delta (b^2 * 4ac) : " << (pow(b, 2)) - 4 * a * c;
}
