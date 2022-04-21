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

NAME = vector

CC = clang++
CFLAGS = -Wall -Werror -Wextra -std=c++98 -fsanitize=address

TEST_UTILITIES_PATH = testUtilities

TEST_UTILITIES_SRC = $(TEST_UTILITIES_PATH)/constructor.cpp \
					 $(TEST_UTILITIES_PATH)/court.cpp \
					 $(TEST_UTILITIES_PATH)/fillVector.cpp \
					 $(TEST_UTILITIES_PATH)/insert.cpp \
					 $(TEST_UTILITIES_PATH)/testUtilities.cpp

TEST_UTILITIES_HDR = $(TEST_UTILITIES_PATH)/court.hpp \
					 $(TEST_UTILITIES_PATH)/testUtilities.hpp

SRC = main.cpp $(TEST_UTILITIES_SRC)

HDR = vector.hpp vectorIterator.hpp $(TEST_UTILITIES_HDR)

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