# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Camille <private_mail>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/20 10:13:22 by Camille           #+#    #+#              #
#    Updated: 2026/08/04 17:48:55 by aiga             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := cub3D

BLUE  := \033[38;5;33m
GREEN  := \033[0;32m
CYAN   := \033[0;36m
YELLOW := \033[0;33m
BOLD   := \033[1m
RESET  := \033[0m

#LIBMLX_DIR := libmlx/
#LIBMLX:= $(LIBMLX_DIR)libmlx.so
#LIBMLXFLAG := -lSDL2

LIBFT_DIR := libft/
LIBFT_NAME := libft.a
LIBFT := $(LIBFT_DIR)$(LIBFT_NAME)
MAKEFLAGS += --no-print-directory

LIBS := $(LIBFT_DIR)
INCLUDES := -Iinclude $(addprefix -I, $(addsuffix include, $(LIBS)))
#LIBS := $(LIBMLX_DIR)
#INCLUDES += $(addprefix -I, $(addsuffix includes, $(LIBS)))

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
PARSER_DIR := parser/

SRC_BASENAMES := main error_manager parser
PARSER_BASENAMES := element_infos element_map
SRCS := $(addprefix $(SRC_DIR), $(addsuffix .c,$(SRC_BASENAMES))) \
		$(addprefix $(SRC_DIR)$(PARSER_DIR), $(addsuffix .c,$(PARSER_BASENAMES)))

OBJ_DIR := .build/
OBJS := $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

all: $(NAME)

#TODO: ajouter la libmlx pour les lignes suivante, voir solong
$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $^ -o $@ $(LIBFT)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) -j
	@printf "$(CYAN)Compiling$(RESET) $(BOLD)%s			$(GREEN)[OK]\n" $<

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)$(PARSER_DIR)
	@printf "$(CYAN)Compiling$(RESET) $(BOLD)%s			$(GREEN)[OK]\n" $<
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@printf "$(GREEN)Cleaned objs files!\n$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@printf "$(GREEN)Cleaned $(NAME) and libraries!\n$(RESET)"

re: fclean all

.PHONY: all clean fclean re
