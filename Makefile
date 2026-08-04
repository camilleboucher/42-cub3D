CC := cc
CFLAGS := -Wall -Wextra -Werror -g -O3 -Wno-unused-result
LDFLAGS = -lSDL2 -lm

NAME := so_long

OUTPUT_DIR := output

SRC_DIR := src

SRC := $(SRC_DIR)/ui.c

INCLUDES := list,gnl,libft,ft_printf,include,MacroLibX

OBJ := $(SRC:$(SRC_DIR)/%.c=$(OUTPUT_DIR)/%.o)

$(NAME): $(OUTPUT_DIR) $(OBJ) $(OUTPUT_DIR)/main.o MacroLibX/libmlx.so libft/libft.a ft_printf/libftprintf.a
	$(CC) $(OBJ) $(OUTPUT_DIR)/main.o MacroLibX/libmlx.so libft/libft.a ft_printf/libftprintf.a $(CFLAGS) $(LDFLAGS) -o $@

$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)/gnl $(OUTPUT_DIR)/list

$(OUTPUT_DIR)/main_bonus.o: $(SRC_DIR)/main_bonus.c $(OUTPUT_DIR)
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDES)

$(OUTPUT_DIR)/main.o: $(SRC_DIR)/main.c $(OUTPUT_DIR)
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDES)

$(OUTPUT_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDES)

MacroLibX/libmlx.so:
	make -C MacroLibX -j10

libft/libft.a:
	make -C libft

ft_printf/libftprintf.a:
	make -C ft_printf

all: $(NAME)

bonus: $(OUTPUT_DIR) $(OBJ) $(OUTPUT_DIR)/main_bonus.o MacroLibX/libmlx.so libft/libft.a ft_printf/libftprintf.a
	$(CC) $(OBJ) $(OUTPUT_DIR)/main_bonus.o MacroLibX/libmlx.so libft/libft.a ft_printf/libftprintf.a $(CFLAGS) $(LDFLAGS) -o $(NAME)

clean:
	rm -rf $(OUTPUT_DIR)
	make -C MacroLibX fclean
	make -C libft fclean
	make -C ft_printf fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean all re fclean bonus