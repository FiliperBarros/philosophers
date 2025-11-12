# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frocha-b <frocha-b@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/01 16:59:12 by frocha-b          #+#    #+#              #
#    Updated: 2025/11/12 17:53:05 by frocha-b         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

#Compiler and flags
CC 			= cc
CFLAGS		= -Wall -Werror -Wextra -fsanitize=thread -g 

#Source and objects directories
SRC_DIR 	= src
OBJ_DIR 	= objects

SRC_FILES 	= $(shell find $(SRC_DIR) -name "*.c")

#Converts the source files in object files
OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

#Include paths
PHILO_INC	= -Iincludes

# Tell make where to search for source files
VPATH		= $(SRC_DIR) $(SRC_DIR)/utils	

# **************************************************************************** #
#                                MAKE RULES                                    #
# **************************************************************************** #

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(PHILO_INC)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re valgrind
	