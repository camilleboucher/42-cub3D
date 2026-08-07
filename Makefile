CC := cc
CFLAGS := -Wall -Wextra -g -O3 -Wno-unused-result
LDFLAGS = -lSDL2 -lm

NAME := cube

OUTPUT_DIR := output

SRC_DIR := src

SRC := $(SRC_DIR)/gui/ui.c \
	   $(SRC_DIR)/app/init.c \
	   $(SRC_DIR)/vector2/vec2f.c \
	   $(SRC_DIR)/vector2/vec2i.c \
	   $(SRC_DIR)/menus/main_menu.c \
	   $(SRC_DIR)/atlas/atlas.c \
	   $(SRC_DIR)/frame_buffer/alloc.c \
	   $(SRC_DIR)/frame_buffer/interface.c \
	   $(SRC_DIR)/shaders/blur.c \
	   $(SRC_DIR)/main.c

INCLUDES := -Iinclude -IMacroLibX/includes

OBJ := $(SRC:$(SRC_DIR)/%.c=$(OUTPUT_DIR)/%.o)

$(NAME): $(OUTPUT_DIR) $(OBJ) MacroLibX/libmlx.so
	$(CC) $(OBJ) MacroLibX/libmlx.so $(CFLAGS) $(LDFLAGS) -o $@

$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR) $(OUTPUT_DIR)/gui $(OUTPUT_DIR)/vector2 $(OUTPUT_DIR)/app $(OUTPUT_DIR)/menus $(OUTPUT_DIR)/atlas $(OUTPUT_DIR)/frame_buffer $(OUTPUT_DIR)/shaders

$(OUTPUT_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDES)

MacroLibX/libmlx.so:
	make -C MacroLibX -j10

all: $(NAME)

bonus:
	@echo not implemented btw

clean:
	rm -rf $(OUTPUT_DIR)
	make -C MacroLibX fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean all re fclean bonus