/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseExpression.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alex <Alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 11:03:19 by ale-goff          #+#    #+#             */
/*   Updated: 2019/05/14 01:19:55 by Alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseExpression.hpp"

ParseExpression::ParseExpression( std::string expr ) : _expr(expr), _idx(0) {
    _expr.erase(remove_if(_expr.begin(), _expr.end(), isspace), _expr.end());
    return ;
}

ParseExpression::~ParseExpression( void ) { 
    return ;
}

ParseExpression::ParseExpression( ParseExpression const & rhs ) {
    *this = rhs;
}

ParseExpression & ParseExpression::operator=(ParseExpression const & rhs) {
    this->_expr = rhs._expr;
    return *this;
}

ParseExpression::BadExpression::BadExpression( void ) {
    return ;
}

ParseExpression::BadExpression::~BadExpression( void ) throw() {
    return ;
}

const char *ParseExpression::BadExpression::what( void ) const throw() {
    return "Bad expression";
}

MapData<int, int>  & ParseExpression::getMapData( void )  {
    return this->_val;
}

int        ParseExpression::acceptSign( void ) {
    int     sign;
    int     count = 0;

    sign = 1;
    if (IS_OP(_expr[_idx]) && (!_expr[_idx + 1] || (!isdigit(_expr[_idx + 1]) && !IS_OP(_expr[_idx + 1])))) {
        throw BadExpression();
    }
    while (_expr[_idx] == '-') {
        count++;
        sign = -1;
        _idx++;
    } while (_expr[_idx] == '+') {
        _idx++;
    }
	sign = count % 2 == 0 ? 1 : -1; 
    if (_expr[_idx] == '=') {
        sign = -1;
        _idx++;
    }
    return sign;
} 

float        ParseExpression::acceptNumber( void ) {
    int     num;
    char    *end;

    if (_expr[_idx] != 'x') {
        num = std::strtol(&_expr.c_str()[_idx], &end, 10);
        std::string tmp = std::to_string(num);
        _idx += tmp.size() ;
    } else {
        num = 1;
    }
    return num;
}


int        ParseExpression::acceptExponent( void ) {
    int     e;

    e = 0;
    if (_expr[_idx] == 'x') {
        e = 1;
        _idx++;
        if (_expr[_idx] == '^') {
            _idx++;
            if (!_expr[_idx] || (isdigit(_expr[_idx]) == false && _expr[_idx] != '-')) {
                throw BadExpression();
            }
            e = acceptNumber();
        }
    }
    return e;
}

float        ParseExpression::acceptCoefficient() {
    float       n;
    int         sign;

    sign = acceptSign();
    n = acceptNumber();
    return n * sign;
}

bool        ParseExpression::acceptTerm( void ) {
    float     n;
    int     e;

    if (_idx >= static_cast<int>(_expr.size()))
        return false;
    n = acceptCoefficient();
    e = acceptExponent();
    // _val.insert(std::pair<float, int>(e, n));
    this->_val.myInsert(e, n);
    return acceptTerm();
}

