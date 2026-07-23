# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Camille <private_mail>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/20 10:13:22 by Camille           #+#    #+#              #
#    Updated: 2026/07/23 19:06:14 by aiga             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := cub3D

BLUE  := \033[38;5;33m
GREEN  := \033[0;32m
CYAN   := \033[0;36m
YELLOW := \033[0;33m
BOLD   := \033[1m
RESET  := \033[0m

INCLUDES := -Iinclude

CC := cc
CFLAGS := -Wall -Werror -Wextra $(INCLUDES)
ifeq ($(DEBUG),true)
    CFLAGS += -g
endif
ifeq ($(FSANITIZE), true)
	CFLAGS += -fsanitize=address
endif
ifeq ($(FSANITIZE_THREAD), true)
    CFLAGS += -fsanitize=thread
endif

SRC_DIR := src/

SRC_BASENAMES := main errors_manager parsing
SRCS := $(addprefix $(SRC_DIR), $(addsuffix .c,$(SRC_BASENAMES)))

OBJ_DIR := .build/
OBJS := $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@printf "$(CYAN)Compiling$(RESET) $(BOLD)%s			$(GREEN)[OK]\n" $<
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)
	@printf "$(GREEN)Cleaned everything!\n$(RESET)Enjoy the Free Space!\n"

re: fclean all

.PHONY: all clean fclean re
