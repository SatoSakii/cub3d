# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albernar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/16 17:32:26 by albernar          #+#    #+#              #
#    Updated: 2025/03/24 18:20:27 by albernar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# VARIABLES
CC 			:= cc
FLAGS 		:= -Wall -Wextra -Werror -g -D VULKAN_NO_PROTOTYPES -D IMGUI_IMPL_VULKAN_NO_PROTOTYPES -D CIMGUI_USE_VULKAN -D CIMGUI_USE_SDL2

# INCLUDES
INCLUDES_COMMON		:=	-Ilib/MacroLibX/includes -Ilib/libft/includes \
						-Iincludes/common

INCLUDES_MANDATORY	:=	$(INCLUDES_COMMON) \
						-Iincludes/mandatory

INCLUDES_BONUS		:=	$(INCLUDES_COMMON) \
						-Ilib/third_party/includes \
						-Ilib/cimgui -Iincludes/bonus

# FOLDERS
OBJ_DIR 		= .build
SRC_DIR 		= srcs
MANDATORY_DIR	= mandatory
BONUS_DIR 		= bonus
COMMON_DIR 		= common

# SOURCES
LIBMLX_PATH = ./lib/MacroLibX
LIBFT_PATH	= ./lib/libft
CIMGUI_PATH = ./lib/cimgui

COMMON		:=	$(COMMON_DIR)/parsing/args/args_validation.c \
				$(COMMON_DIR)/parsing/data/colors/parse_colors.c \
				$(COMMON_DIR)/parsing/data/map/map_creator.c \
				$(COMMON_DIR)/parsing/data/map/map_validation.c \
				$(COMMON_DIR)/parsing/data/map/parse_map.c \
				$(COMMON_DIR)/parsing/data/textures/parse_textures.c \
				$(COMMON_DIR)/parsing/data/parse_file.c \
				$(COMMON_DIR)/parsing/data/parse_utils.c \
				$(COMMON_DIR)/parsing/dynamic_parser/parser_getter_list.c \
				$(COMMON_DIR)/parsing/dynamic_parser/parser_getter.c \
				$(COMMON_DIR)/parsing/dynamic_parser/parser_register.c \
				$(COMMON_DIR)/parsing/dynamic_parser/parser_utils.c \
				$(COMMON_DIR)/parsing/dynamic_parser/parser.c \
				$(COMMON_DIR)/parsing/error/error_ctx.c \
				$(COMMON_DIR)/parsing/error/error_print.c \
				$(COMMON_DIR)/utils/render/memset_uint8.c \
				$(COMMON_DIR)/utils/times/delta_time.c \
				$(COMMON_DIR)/utils/times/fps.c

SRCS		:=	$(COMMON) \
				$(MANDATORY_DIR)/core/main.c \
				$(MANDATORY_DIR)/events/hooks.c \
				$(MANDATORY_DIR)/events/moves.c \
				$(MANDATORY_DIR)/render/raycast_textures_utils.c \
				$(MANDATORY_DIR)/render/raycast_utils.c \
				$(MANDATORY_DIR)/render/raycast.c \
				$(MANDATORY_DIR)/utils/game/free_game.c \
				$(MANDATORY_DIR)/utils/game/init_game.c

SRCS := $(addprefix $(SRC_DIR)/, $(SRCS))

SRCS_BONUS	:=	$(COMMON) \
				$(BONUS_DIR)/core/main.c \
				$(BONUS_DIR)/events/hooks/keydown.c \
				$(BONUS_DIR)/events/hooks/keyup.c \
				$(BONUS_DIR)/events/hooks/loop.c \
				$(BONUS_DIR)/events/hooks/mousedown.c \
				$(BONUS_DIR)/events/hooks/mouseup.c \
				$(BONUS_DIR)/events/hooks/window.c \
				$(BONUS_DIR)/events/player/collision.c \
				$(BONUS_DIR)/events/player/move.c \
				$(BONUS_DIR)/render/raycast/raycast_draw.c \
				$(BONUS_DIR)/render/raycast/raycast_hit.c \
				$(BONUS_DIR)/render/raycast/raycast_init.c \
				$(BONUS_DIR)/render/raycast/raycast_tex.c \
				$(BONUS_DIR)/render/raycast/raycast.c \
				$(BONUS_DIR)/utils/game/free.c \
				$(BONUS_DIR)/utils/game/init_mlx.c \
				$(BONUS_DIR)/utils/game/init.c \
				$(BONUS_DIR)/utils/game/menu.c \
				$(BONUS_DIR)/utils/render/background.c

SRCS_BONUS := $(addprefix $(SRC_DIR)/, $(SRCS_BONUS))

# OBJECTS
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/mandatory/%.o, $(SRCS))
OBJS_BONUS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/bonus/%.o, $(SRCS_BONUS))

# EXECUTABLES
NAME = cub3D
NAME_BONUS = cub3D_bonus

# RULES
all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(LIBMLX_PATH)/libmlx.so $(LIBFT_PATH)/libft.a $(OBJS)
	@$(CC) $(FLAGS) $(INCLUDES_MANDATORY) $(OBJS) $(LIBFT_PATH)/libft.a $(LIBMLX_PATH)/libmlx.so -lSDL2 -lm -o $(NAME)
	@echo " $(GREEN)$(BOLD)$(ITALIC)■$(RESET)  building	$(GREEN)$(BOLD)$(ITALIC)$(NAME)$(RESET)"

$(NAME_BONUS): $(LIBMLX_PATH)/libmlx.so $(LIBFT_PATH)/libft.a $(CIMGUI_PATH)/cimgui.so $(OBJS_BONUS)
	@$(CC) $(FLAGS) $(INCLUDES_BONUS) $(OBJS_BONUS) $(LIBFT_PATH)/libft.a $(LIBMLX_PATH)/libmlx.so $(CIMGUI_PATH)/cimgui.so -lSDL2 -lm -o $(NAME_BONUS)
	@echo " $(GREEN)$(BOLD)$(ITALIC)■$(RESET)  building	$(GREEN)$(BOLD)$(ITALIC)$(NAME_BONUS)$(RESET)"

$(LIBMLX_PATH)/libmlx.so:
	@echo "$(YELLOW)Compiling MLX42...$(RESET)"
	@make -C $(LIBMLX_PATH) -s -j
	@echo "$(GREEN)MLX42 created successfully!$(RESET)"
	
$(LIBFT_PATH)/libft.a:
	@echo "$(YELLOW)Compiling Libft...$(RESET)"
	@make -C $(LIBFT_PATH) -s
	@echo "$(GREEN)Libft created successfully!$(RESET)"

$(CIMGUI_PATH)/cimgui.so:
	@make -f ./lib/cimgui.mk -j12

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo " $(CYAN)$(BOLD)$(ITALIC)■$(RESET)  compiling	$(GRAY)$(BOLD)$(ITALIC)$<$(RESET)"
	@$(CC) $(FLAGS) $(INCLUDES_COMMON) -o $@ -c $<

$(OBJ_DIR)/mandatory/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo " $(CYAN)$(BOLD)$(ITALIC)■$(RESET)  compiling	$(GRAY)$(BOLD)$(ITALIC)$<$(RESET)"
	@$(CC) $(FLAGS) $(INCLUDES_MANDATORY) -o $@ -c $<

$(OBJ_DIR)/bonus/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo " $(CYAN)$(BOLD)$(ITALIC)■$(RESET)  compiling	$(GRAY)$(BOLD)$(ITALIC)$<$(RESET)"
	@$(CC) $(FLAGS) -D BONUS $(INCLUDES_BONUS) -o $@ -c $<

clean:
	@make clean -C $(LIBFT_PATH) -s
	@make clean -C $(LIBMLX_PATH) -s
	@make clean -C $(CIMGUI_PATH) -s
	@echo " $(RED)$(BOLD)$(ITALIC)■$(RESET)  cleaned	$(RED)$(BOLD)$(ITALIC)$(MLX_DIR)$(RESET)"
	@rm -rf $(OBJ_DIR)
	
fclean:
	@echo "$(RED)Cleaning MLX42 files...$(RESET)"
	@make fclean -C $(LIBMLX_PATH) -s
	@make fclean -C $(LIBFT_PATH) -s
	@make fclean -C $(CIMGUI_PATH) -s
	@echo "$(RED)Cleaning executables...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME) $(NAME_BONUS)
	
remake: clean all

re: fclean all

.PHONY: all bonus clean fclean remake re

BLACK		=	\033[30m
RED			=	\033[31m
GREEN		=	\033[32m
YELLOW		=	\033[33m
BLUE		=	\033[34m
MAGENTA		=	\033[35m
CYAN		=	\033[36m
WHITE		=	\033[37m
GRAY		=	\033[90m

BOLD		=	\033[1m
ITALIC		=	\033[3m

RESET		=	\033[0m
LINE_CLR	=	\33[2K\r