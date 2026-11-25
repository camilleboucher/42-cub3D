CC := cc
CFLAGS := -Wall -Wextra -Wno-unused-result -march=native -flto -O3 -Werror
LDFLAGS = -flto -lSDL2 -lm

ifeq ($(FSANITIZE), true)
	CFLAGS += -fsanitize=address
endif

ifeq ($(DEBUG), true)
	CFLAGS += -g
else
	CFLAGS += -O3 -march=native -flto
endif

NAME := cub3D
NAME_BONUS := $(NAME)_bonus

OUTPUT_DIR := output
OUTPUT_DIR_BONUS := $(OUTPUT_DIR)_bonus

SRC_DIR := src
SRC_DIR_BONUS := $(SRC_DIR)_bonus

SRC := $(SRC_DIR)/app/init.c \
	   $(SRC_DIR)/data_structures/vec2f_math.c \
	   $(SRC_DIR)/data_structures/vec2f_utils.c \
	   $(SRC_DIR)/data_structures/vec2i.c \
	   $(SRC_DIR)/app/atlas.c \
	   $(SRC_DIR)/frame_buffer/alloc.c \
	   $(SRC_DIR)/frame_buffer/interface.c \
	   $(SRC_DIR)/main.c \
	   $(SRC_DIR)/app/error_manager.c \
	   $(SRC_DIR)/parser/parser.c \
	   $(SRC_DIR)/parser/map_parser.c \
	   $(SRC_DIR)/parser/element_infos.c \
	   $(SRC_DIR)/parser/element_map.c \
	   $(SRC_DIR)/parser/parser_utils.c \
	   $(SRC_DIR)/app/cleaner.c \
	   $(SRC_DIR)/game/game.c \
	   $(SRC_DIR)/raycaster/raycast.c \
	   $(SRC_DIR)/app/tools.c \
	   $(SRC_DIR)/input/handler.c \
	   $(SRC_DIR)/input/device.c \
	   $(SRC_DIR)/game/player/player.c \
	   $(SRC_DIR)/input/device_utils.c \
	   $(SRC_DIR)/raycaster/raycast_utils.c \
	   $(SRC_DIR)/raycaster/filling.c \
	   $(SRC_DIR)/frame_buffer/clear.c \
	   $(SRC_DIR)/frame_buffer/display.c \
	   $(SRC_DIR)/game/player/player_utils.c \
	   $(SRC_DIR)/game/ingame_logic.c \
	   $(SRC_DIR)/input/events.c \
	   $(SRC_DIR)/game/window.c

SRC_BONUS := $(SRC_DIR_BONUS)/gui/ui_bonus.c \
	   $(SRC_DIR_BONUS)/app/init_bonus.c \
	   $(SRC_DIR_BONUS)/data_structures/vec2f_math_bonus.c \
	   $(SRC_DIR_BONUS)/data_structures/vec2f_utils_bonus.c \
	   $(SRC_DIR_BONUS)/data_structures/vec2i_bonus.c \
	   $(SRC_DIR_BONUS)/app/atlas_bonus.c \
	   $(SRC_DIR_BONUS)/frame_buffer/alloc_bonus.c \
	   $(SRC_DIR_BONUS)/frame_buffer/interface_bonus.c \
	   $(SRC_DIR_BONUS)/main_bonus.c \
	   $(SRC_DIR_BONUS)/app/error_manager_bonus.c \
	   $(SRC_DIR_BONUS)/parser/parser_bonus.c \
	   $(SRC_DIR_BONUS)/parser/map_parser_bonus.c \
	   $(SRC_DIR_BONUS)/parser/element_infos_bonus.c \
	   $(SRC_DIR_BONUS)/parser/element_map_bonus.c \
	   $(SRC_DIR_BONUS)/parser/parser_utils_bonus.c \
	   $(SRC_DIR_BONUS)/app/cleaner_bonus.c \
	   $(SRC_DIR_BONUS)/game/game_bonus.c \
	   $(SRC_DIR_BONUS)/game/objects_bonus.c \
	   $(SRC_DIR_BONUS)/raycaster/raycast_bonus.c \
	   $(SRC_DIR_BONUS)/gui/minimap_bonus.c \
	   $(SRC_DIR_BONUS)/app/tools_bonus.c \
	   $(SRC_DIR_BONUS)/input/handler_bonus.c \
	   $(SRC_DIR_BONUS)/input/device_bonus.c \
	   $(SRC_DIR_BONUS)/game/player/player_bonus.c \
	   $(SRC_DIR_BONUS)/raycaster/billboards_bonus.c \
	   $(SRC_DIR_BONUS)/input/device_utils_bonus.c \
	   $(SRC_DIR_BONUS)/raycaster/raycast_utils_bonus.c \
	   $(SRC_DIR_BONUS)/raycaster/filling_bonus.c \
	   $(SRC_DIR_BONUS)/gui/ui_create_bonus.c \
	   $(SRC_DIR_BONUS)/gui/minimap_drawing_bonus.c \
	   $(SRC_DIR_BONUS)/gui/ui_card_bonus.c \
	   $(SRC_DIR_BONUS)/gui/ui_utils_bonus.c \
	   $(SRC_DIR_BONUS)/raycaster/billboards_sorting_bonus.c \
	   $(SRC_DIR_BONUS)/graphic/animated_sprite_bonus.c \
	   $(SRC_DIR_BONUS)/frame_buffer/clear_bonus.c \
	   $(SRC_DIR_BONUS)/frame_buffer/display_bonus.c \
	   $(SRC_DIR_BONUS)/game/player/player_utils_bonus.c \
	   $(SRC_DIR_BONUS)/game/ingame_logic_bonus.c \
	   $(SRC_DIR_BONUS)/input/events_bonus.c \
	   $(SRC_DIR_BONUS)/input/select_menu_logic_bonus.c \
	   $(SRC_DIR_BONUS)/game/main_menu_logic_bonus.c \
	   $(SRC_DIR_BONUS)/input/mouse_bonus.c \
	   $(SRC_DIR_BONUS)/game/player/player_count_menu_bonus.c \
	   $(SRC_DIR_BONUS)/game/player/player_interact_bonus.c \
	   $(SRC_DIR_BONUS)/game/window_bonus.c \
	   $(SRC_DIR_BONUS)/raycaster/filling_door_bonus.c

INCLUDES := -Iinclude -IMacroLibX/includes -Ilibft/include
INCLUDES_BONUS := -Iinclude_bonus -IMacroLibX/includes -Ilibft/include

OBJ := $(SRC:$(SRC_DIR)/%.c=$(OUTPUT_DIR)/%.o)
OBJ_BONUS := $(SRC_BONUS:$(SRC_DIR_BONUS)/%.c=$(OUTPUT_DIR_BONUS)/%.o)

$(NAME): MacroLibX/libmlx.so $(OUTPUT_DIR) $(OBJ) libft/libft.a
	$(CC) $(OBJ) MacroLibX/libmlx.so libft/libft.a $(CFLAGS) $(LDFLAGS) -o $@ libft/libft.a
$(NAME_BONUS): MacroLibX/libmlx.so $(OUTPUT_DIR_BONUS) $(OBJ_BONUS) libft/libft.a
	$(CC) $(OBJ_BONUS) MacroLibX/libmlx.so libft/libft.a $(CFLAGS) $(LDFLAGS) -o $@ libft/libft.a

$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR) $(OUTPUT_DIR)/input $(OUTPUT_DIR)/graphic \
		$(OUTPUT_DIR)/tools $(OUTPUT_DIR)/game $(OUTPUT_DIR)/gui \
		$(OUTPUT_DIR)/data_structures $(OUTPUT_DIR)/app \
	    $(OUTPUT_DIR)/frame_buffer $(OUTPUT_DIR)/parser \
		$(OUTPUT_DIR)/raycaster $(OUTPUT_DIR)/animated_sprite $(OUTPUT_DIR)/game/player

$(OUTPUT_DIR_BONUS):
	mkdir -p $(OUTPUT_DIR_BONUS) $(OUTPUT_DIR_BONUS)/input $(OUTPUT_DIR_BONUS)/graphic \
		$(OUTPUT_DIR_BONUS)/tools $(OUTPUT_DIR_BONUS)/game $(OUTPUT_DIR_BONUS)/gui \
		$(OUTPUT_DIR_BONUS)/data_structures $(OUTPUT_DIR_BONUS)/app \
	    $(OUTPUT_DIR_BONUS)/frame_buffer $(OUTPUT_DIR_BONUS)/parser \
		$(OUTPUT_DIR_BONUS)/raycaster $(OUTPUT_DIR_BONUS)/animated_sprite $(OUTPUT_DIR_BONUS)/game/player

$(OUTPUT_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDES)

$(OUTPUT_DIR_BONUS)/%.o: $(SRC_DIR_BONUS)/%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDES_BONUS)

MacroLibX/libmlx.so:
	if [ ! -f MacroLibX/Makefile ]; then git submodule init && git submodule update; fi
	make -C MacroLibX -j

libft/libft.a:
	make -C libft

all: $(NAME)
bonus: $(NAME_BONUS)

clean:
	rm -rf $(OUTPUT_DIR)
	rm -rf $(OUTPUT_DIR_BONUS)
ifneq ($(RE_NO_MLX), true)
	make -C MacroLibX fclean
endif
	make -C libft fclean

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus
