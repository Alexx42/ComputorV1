/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computorv1.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 10:54:03 by ale-goff          #+#    #+#             */
/*   Updated: 2019/05/15 14:24:52 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseExpression.hpp"
#include <cmath>

int         main(int ac, char **av) {
    if (ac != 2) {
        std::cout << "usage: ./ComputorV1 [expression]" << std::endl;
        return (1);
    }
    ParseExpression expr = ParseExpression(av[1]);
    try {
        expr.acceptTerm();
    }catch (ParseExpression::BadExpression &e) {
        std::cout << e.what() << std::endl;
        return (1);
    }
    MapData<int, float>::iterator it = expr.getMapData().getMap()->begin();
    MapData<int, float>::iterator ite = expr.getMapData().getMap()->end();
    int max = 0;
	std::cout << "Refactored expression: ";
    while (it != ite) {
        if (it->first > max) {
            max = it->first;
        }
		if (it->second > 0 && it != expr.getMapData().getMap()->begin()) {
			std::cout << "+ ";
		}
		std::cout << it->second;
		if (it->first != 0) {
			std::cout << "x^" << it->first;
		}
		std::cout << " ";
        it++; 
    }
	std::cout << "= 0";
	float		a;
    try {
        a = expr.getMapData().getMap()->at(2);
    } catch (std::out_of_range) {
        a = 0;
    }
	float		b;
    try {
        b = expr.getMapData().getMap()->at(1);
    }
    catch (std::out_of_range) {
        b = 0;
    }
	float		c;
    try {
        c = expr.getMapData().getMap()->at(0);
    } catch (std::out_of_range) {
        c = 0;
    }
	std::cout << std::endl;
    float       delta = (pow(b, 2)) - 4 * a * c;
    float         x0;
    float         x1;
    float         x2;
            std::cout << "Polynomial degreee : " << max << std::endl;
    if (max == 0) {
        std::cout << "x = " << c << std::endl;
    }
    else if (max == 2) {
        
        std::cout << "Delta (b^2 * 4ac) : " << delta << std::endl << std::endl;
        std::cout << "Solution : " << std::endl;
        if (delta == 0) {
            std::cout << "Since delta equals 0, only one solution" << std::endl;
            x0 = -b / (2 * a);
            std::cout << "x0 = " << x0 << std::endl;
        } else if (delta > 0) {
            std::cout << "Delta is superior than 0, 2 solutions" << std::endl;
            x1 = (- b - sqrt(delta)) / (2 * a);
            x2 = (- b + sqrt(delta)) / (2 * a);
            std::cout << "x1 = " << x1 << std::endl << "x2 = " << x2 << std::endl;
        } else {
            std::cout << "Delta is less than 0, 2 solutions" << std::endl;
            int denom = 2 * a;
            std::cout << -b / denom << (-(sqrt(-delta))) / (2 * a)  << "i" << std::endl;
        }
    } else if (max == 1) {
        x0 = c * - 1;
        x0 /= b;
        std::cout << "x = " << x0 << std::endl; 
    } else {
        std::cout << "The polynomial degree is strictly greater than 2, I can't solve it" << std::endl;
    }
    return (1);
}
