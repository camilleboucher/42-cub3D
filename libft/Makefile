# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Camille <private_mail>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/20 10:13:22 by Camille           #+#    #+#              #
#    Updated: 2025/11/10 18:57:14 by Camille          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libft.a

CC := cc
CFLAGS := -Wall -Werror -Wextra -Iinclude
ifeq ($(DEBUG),true)
    CFLAGS += -g
endif
AR := ar
ARFLAGS := rcs

SRC_DIR := src/

CTYPE_DIR := ctype/
LIST_DIR := data_structures/list/
GNL_DIR := get_next_line/
STDIO_DIR := stdio/
PRINTF_DIR := stdio/ft_printf/
STDLIB_DIR := stdlib/
STRING_DIR := string/
STRUTILS_DIR := strutils/

CTYPE_BASENAMES := ft_isalnum ft_isascii ft_isprint ft_toupper ft_isalpha \
				   ft_isdigit ft_tolower ft_isspace
LIST_BASENAMES := ft_lstadd_back ft_lstclear ft_lstiter ft_lstmap ft_lstsize \
				  ft_lstadd_front ft_lstdelone ft_lstlast ft_lstnew
GNL_BASENAMES := get_next_line
STDIO_BASENAMES := ft_putchar_fd ft_putendl_fd ft_putnbr_fd ft_putstr_fd
PRINTF_BASENAMES := ft_printf print_decimal print_pointer \
					   print_hexadecimal print_string print_char \
					   print_percent_sign print_unsigned_decimal
STDLIB_BASENAMES := ft_atoi ft_calloc ft_itoa
STRING_BASENAMES := ft_bzero ft_memcpy ft_strchr ft_strlcpy ft_strnstr ft_memchr \
			  ft_memmove ft_strdup ft_strlen ft_strrchr ft_memcmp ft_memset \
			  ft_strlcat ft_strncmp
STRUTILS_BASENAMES := ft_split ft_striteri ft_strjoin ft_strmapi ft_strtrim ft_substr

SRC_CTYPE := $(addprefix $(SRC_DIR)$(CTYPE_DIR), \
			 $(addsuffix .c,$(CTYPE_BASENAMES)))
SRC_DATA_STRUCTURES := $(addprefix $(SRC_DIR)$(LIST_DIR), \
					   $(addsuffix .c,$(LIST_BASENAMES)))
SRC_GNL := $(addprefix $(SRC_DIR)$(GNL_DIR), \
		   $(addsuffix .c,$(GNL_BASENAMES)))
SRC_STDIO := $(addprefix $(SRC_DIR)$(STDIO_DIR), \
			 $(addsuffix .c,$(STDIO_BASENAMES))) \
			 $(addprefix $(SRC_DIR)$(PRINTF_DIR), \
			 $(addsuffix .c,$(PRINTF_BASENAMES)))
SRC_STDLIB := $(addprefix $(SRC_DIR)$(STDLIB_DIR), \
			  $(addsuffix .c,$(STDLIB_BASENAMES)))
SRC_STRING := $(addprefix $(SRC_DIR)$(STRING_DIR), \
			  $(addsuffix .c,$(STRING_BASENAMES)))
SRC_STRUTILS := $(addprefix $(SRC_DIR)$(STRUTILS_DIR), \
				$(addsuffix .c,$(STRUTILS_BASENAMES)))

SRCS := $(SRC_CTYPE) $(SRC_DATA_STRUCTURES) $(SRC_GNL) $(SRC_STDIO) \
		$(SRC_STDLIB) $(SRC_STRING) $(SRC_STRUTILS)
# OBJ_CTYPE  := $(SRC_CTYPE:.c=.o)

OBJ_DIR := .build/
OBJS := $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)$(CTYPE_DIR)
	@mkdir -p $(OBJ_DIR)$(LIST_DIR)
	@mkdir -p $(OBJ_DIR)$(GNL_DIR)
	@mkdir -p $(OBJ_DIR)$(STDIO_DIR)
	@mkdir -p $(OBJ_DIR)$(PRINTF_DIR)
	@mkdir -p $(OBJ_DIR)$(STDLIB_DIR)
	@mkdir -p $(OBJ_DIR)$(STRING_DIR)
	@mkdir -p $(OBJ_DIR)$(STRUTILS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
