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

NAME = containers

CC = clang++
CFLAGS = -Wall -Werror -Wextra -std=c++98 -fsanitize=address


#algorithm
#================================================================================
ALGORITHM_PATH = algorithm

ALGORITHM_SRC = 

ALGORITHM_HRC = $(ALGORITHM_PATH)/algorithm.hpp
#================================================================================

#iterator
#================================================================================
ITERATOR_PATH = iterator

ITERATOR_SRC = 

ITERATOR_HRC = $(ITERATOR_PATH)/iterator.hpp \
			   $(ITERATOR_PATH)/iterator_traits.hpp \
			   $(ITERATOR_PATH)/reverse_iterator.hpp
#================================================================================

#type_traits
#================================================================================
TYPE_TRAITS_PATH = type_traits

TYPE_TRAITS_SRC = 

TYPE_TRAITS_HRC = $(TYPE_TRAITS_PATH)/type_traits.hpp
#================================================================================

#utility
#================================================================================
UTILITY_PATH = utility

UTILITY_SRC = 

UTILITY_HRC = $(UTILITY_PATH)/make_pair.hpp \
			  $(UTILITY_PATH)/pair.hpp \
			  $(UTILITY_PATH)/utility.hpp
#================================================================================

#map
#================================================================================
MAP_PATH = map

MAP_SRC = 

MAP_HRC = $(MAP_PATH)/map.hpp \
		  $(MAP_PATH)/node.hpp \
		  $(MAP_PATH)/treeIterator.hpp
#================================================================================

#vector
#================================================================================
VECTOR_PATH = vector

VECTOR_SRC = 

VECTOR_SRC = $(VECTOR_PATH)/vector.hpp \
			 $(VECTOR_PATH)/vectorIterator.hpp
#================================================================================

#stack
#================================================================================
STACK_PATH = 
STACK_SRC = 
#================================================================================

#tests
#================================================================================
TESTS_PATH = tests
#================================================================================

#vector tests
#================================================================================
TESTS_VECTOR_PATH = $(TESTS_PATH)/vector

TESTS_VECTOR_SRC = $(TESTS_VECTOR_PATH)/fillVector.cpp

TESTS_VECTOR_HRC = $(TESTS_VECTOR_PATH)/testUtilities.hpp
#================================================================================

#map tests
#================================================================================
TESTS_MAP_PATH = $(TESTS_PATH)/map

TESTS_MAP_SRC = $(TESTS_MAP_PATH)/testMapIterator.cpp

TESTS_MAP_HRC = $(TESTS_MAP_PATH)/testUtilities.hpp
#================================================================================

#tests continued
#================================================================================
TESTS_SRC = $(TESTS_VECTOR_SRC) $(TESTS_MAP_SRC)
TESTS_HRC = $(TESTS_VECTOR_HRC) $(TESTS_MAP_HRC)
#================================================================================


SRC = $(ALGORITHM_SRC) $(ITERATOR_SRC) $(TYPE_TRAITS_SRC) $(UTILITY_SRC) $(MAP_SRC) \
	  $(VECTOR_SRC) $(TESTS_SRC)

HRC = $(ALGORITHM_HRC) $(ITERATOR_HRC) $(TYPE_TRAITS_HRC) $(UTILITY_HRC) $(MAP_HRC) \
	  $(VECTOR_HRC) $(TESTS_HRC)

OBJ = $(SRC:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJ) $(HDR)
	@$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.cpp
	@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY : clean fclean re