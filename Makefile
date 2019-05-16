# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/13 10:47:30 by ale-goff          #+#    #+#              #
#    Updated: 2019/05/15 00:10:04 by ale-goff         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ComputorV1

SRCS = computorv1.cpp ParseExpression.cpp

OBJ = computorv1.o ParseExpression.o

CXX = clang++
CXXFLAGS = -g3 -fsanitize=address -Wall -Werror -Wextra -std=c++98

all: $(NAME)

%.o:%.cpp
	$(CXX) $(CXXFLAGS)  -o $@   -c $< 

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME)  $(OBJ) 

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
