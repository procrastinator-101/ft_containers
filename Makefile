# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youness <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/28 22:37:58 by youness           #+#    #+#              #
#    Updated: 2021/10/20 19:08:26 by yarroubi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

Author = younes

NAME = stlContainers ftContainers

CC = c++
CFLAGS = -Wall -Werror -Wextra -std=c++98 -fsanitize=address


#algorithm
#================================================================================
ALGORITHM_PATH = algorithm

ALGORITHM_SRC = 

ALGORITHM_HDR = $(ALGORITHM_PATH)/algorithm.hpp
#================================================================================

#iterator
#================================================================================
ITERATOR_PATH = iterator

ITERATOR_SRC = 

ITERATOR_HDR = $(ITERATOR_PATH)/iterator.hpp \
			   $(ITERATOR_PATH)/iterator_traits.hpp \
			   $(ITERATOR_PATH)/reverse_iterator.hpp
#================================================================================

#type_traits
#================================================================================
TYPE_TRAITS_PATH = type_traits

TYPE_TRAITS_SRC = 

TYPE_TRAITS_HDR = $(TYPE_TRAITS_PATH)/type_traits.hpp
#================================================================================

#utility
#================================================================================
UTILITY_PATH = utility

UTILITY_SRC = 

UTILITY_HDR = $(UTILITY_PATH)/make_pair.hpp \
			  $(UTILITY_PATH)/pair.hpp \
			  $(UTILITY_PATH)/utility.hpp
#================================================================================

#map
#================================================================================
MAP_PATH = map

MAP_SRC = 

MAP_HDR = $(MAP_PATH)/map.hpp \
		  $(MAP_PATH)/node.hpp \
		  $(MAP_PATH)/treeIterator.hpp
#================================================================================

#vector
#================================================================================
VECTOR_PATH = vector

VECTOR_SRC = 

VECTOR_HDR = $(VECTOR_PATH)/vector.hpp \
			 $(VECTOR_PATH)/vectorIterator.hpp
#================================================================================

#stack
#================================================================================
STACK_PATH = stack
STACK_SRC = 
STACK_HDR = $(STACK_PATH)/stack.hpp
#================================================================================


SRC = main.cpp $(ALGORITHM_SRC) $(ITERATOR_SRC) $(TYPE_TRAITS_SRC) $(UTILITY_SRC) $(MAP_SRC) \
	  $(VECTOR_SRC) $(STACK_SRC)

HDR = $(ALGORITHM_HDR) $(ITERATOR_HDR) $(TYPE_TRAITS_HDR) $(UTILITY_HDR) $(MAP_HDR) \
	  $(VECTOR_HDR) $(STACK_HDR)

# OBJ = $(SRC:.cpp=.o)

all : $(NAME)

stlContainers : $(SRC) $(HDR)
	@$(CC) $(CFLAGS) -o $@ $(SRC)

ftContainers : $(SRC) $(HDR)
	@$(CC) $(CFLAGS) -D FT=1 -o $@ $(SRC)

# %.o: %.cpp
# 	@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY : clean fclean re