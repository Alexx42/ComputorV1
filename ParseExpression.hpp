/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseExpression.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 11:03:25 by ale-goff          #+#    #+#             */
/*   Updated: 2019/05/15 00:05:03 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSEEXPRESSION_HPP
# define PARSEEXPRESSION_HPP

#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <sstream>
#include "MapData.hpp"

# define IS_OP(c) (c == '+' || c == '-' || c == '*' || c == '%' || c == '/')

class ParseExpression {
    public:
        class BadExpression : public std::exception {
            public:
                BadExpression( void );
                ~BadExpression( void ) throw() ;

                const char      *what() const throw();
        };
        ParseExpression( void ){;}
        ParseExpression( char *str );
        ~ParseExpression( void );
        ParseExpression( ParseExpression const & rhs );
        ParseExpression & operator=( ParseExpression const & rhs );

        float     acceptCoefficient( void );
        bool    acceptTerm( void );
        int     acceptExponent(  );
        float   acceptNumber(  );
        int     acceptSign(  );
        float     acceptOperator( float n );
        int     sizeVal( int n );
        MapData<int, float>  & getMapData( void ) ;

    private:
        std::string _expr;
        int     _idx;
        int     _equal;
        MapData<int, float> _val;
};

# endif