/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseExpression.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 11:03:19 by ale-goff          #+#    #+#             */
/*   Updated: 2019/05/15 18:07:21 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseExpression.hpp"

ParseExpression::ParseExpression( char *str ) : _idx(0), _equal(0) {
    _expr = str;
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

MapData<int, float>  & ParseExpression::getMapData( void )  {
    return this->_val;
}

int        ParseExpression::acceptSign( void ) {
    int     sign = 1;
    int     count = 0;

    if (IS_OP(_expr[_idx]) && (!_expr[_idx + 1] || (!isdigit(_expr[_idx + 1]) && !IS_OP(_expr[_idx + 1]) && _expr[_idx + 1] != 'x'))) {
        throw BadExpression();
    }
    if (_equal == 1) {
        count++;
    }
    if (_expr[_idx] == '=') {
        _equal = 1;
        count++;
        _idx++;
    }
    while (_expr[_idx] == '+' || _expr[_idx] == '-') {
        if (_expr[_idx] == '-') {
            count++;
        }
        _idx++;
    }
    sign = count % 2 == 0 ? 1 : -1;
    return sign;
} 

float        ParseExpression::acceptNumber( void ) {
    float     num;

    if (!isdigit(_expr[_idx]) && _expr[_idx] != 'x') {
        throw BadExpression();
    }
    if (_expr[_idx] != 'x') {
        num = std::stof(&_expr[_idx]);
        std::ostringstream tmp;
        tmp << num;
        _idx += tmp.str().size();
        if (_expr[_idx] == '.')
            _idx++;
        while (_expr[_idx] == '0')
            _idx++;
    } else {
        num = 1;
    }
    return num;
}


int        ParseExpression::acceptExponent(  ) {
    int     e;

    e = 0;
    if (_expr[_idx] == 'x' || _expr[_idx] == '^') {
        e = 1;
        _idx++;
        if (_expr[_idx] == '^') {
            _idx++;
            if (!_expr[_idx] || (isdigit(_expr[_idx]) == false && _expr[_idx] != '-')) {
                throw BadExpression();
            }
            if (_expr[_idx] == '0') {
                _idx++;
                e = 0;
            }
            else
                e = acceptNumber();
            if (_expr[_idx] == '^') {
                _idx++;
                e *= acceptNumber();
            }
        }
    }
    return e;
}

float       ParseExpression::acceptOperator( float n) {
    if (_expr[_idx]) {
        if (_expr[_idx] == '/') {
            if (_expr[_idx + 1] == '0') {
                throw BadExpression();
            }
            _idx++;
            n /= acceptNumber();
        } else if (_expr[_idx] == '*') {
             _idx++;
            n *= acceptNumber();
        }
    }
    if (_expr[_idx] && _expr[_idx] == '*') {
        n = acceptOperator( n );
    }
    return n;
}

float        ParseExpression::acceptCoefficient() {
    float       n;
    int         sign;

    sign = acceptSign();
    n = acceptNumber();
    n = acceptOperator( n );
    return n * sign;
}

bool        ParseExpression::acceptTerm( void ) {
    float     n;
    int     e;

    if (_idx >= static_cast<int>(_expr.size()))
        return false;
    n = acceptCoefficient();
    e = acceptExponent();
    n = acceptOperator( n );
    this->_val.myInsert(e, n);
    return acceptTerm();
}

