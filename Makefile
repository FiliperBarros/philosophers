# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frocha-b <frocha-b@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/01 16:59:12 by frocha-b          #+#    #+#              #
#    Updated: 2025/11/13 14:21:12 by frocha-b         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

# Compiler and flags
CC 			= cc
CFLAGS		= -Wall -Werror -Wextra -g -pthread

# Directories
SRC_DIR 	= src
OBJ_DIR 	= objects

SRC_FILES 	= $(shell find $(SRC_DIR) -name "*.c")
OBJS 		= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Includes
PHILO_INC	= -Iincludes

# Colors
GREEN		= \033[0;32m
YELLOW		= \033[1;33m
BLUE		= \033[0;34m	
RESET		= \033[0m

# **************************************************************************** #
#                                MAKE RULES                                    #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(BLUE)🔗 Linking...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✅ Built $(NAME)!$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)🛠️  Compiling $<$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@ $(PHILO_INC)

clean:
	@echo "$(BLUE)🧹 Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(BLUE)🧽 Removing executable...$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
