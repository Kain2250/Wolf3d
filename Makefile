# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/21 19:14:26 by kain2250          #+#    #+#              #
#    Updated: 2020/08/05 11:46:07 by bdrinkin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Определение системных команд
NAME = wolf3d

# Флаги компиляции:
GCC = gcc
CCFLAGS = -Wall -Wextra -Werror
OTHERS_FLAGS = -lm
SDL2_FLAGS = -lSDL2 -liconv  -Wl,-framework,CoreAudio \
	-Wl,-framework,AudioToolbox -Wl,-framework,ForceFeedback \
	-lobjc -Wl,-framework,CoreVideo -Wl,-framework,Cocoa \
	-Wl,-framework,Carbon -Wl,-framework,IOKit \
	-Wl,-weak_framework,QuartzCore -Wl,-weak_framework,Metal \
	-lSDL2_image -lSDL2_mixer

# Список библиотек и их пути:
ALLLIBS = $(CURDIR)/allLibs
LIBFT_DIRECTORY = $(ALLLIBS)/libft
LIBSDL2_DIR = $(ALLLIBS)/SDL2_lib
LIBSDL2 = $(LIBSDL2_DIR)/lib

# Флаги для сборки библиотек
LIBRARIES_LIBFT = -L$(LIBFT_DIRECTORY) -lft
LIBRARIES_SDL2 = -L$(LIBSDL2) $(SDL2_FLAGS)

# Заголовочные файлы и их пути:
INCLUDES_DIRECTORY = $(CURDIR)/includes
INCLUDES_DIRECTORY_LIBFT = $(LIBFT_DIRECTORY)/includes
INCLUDES_SDL2 = $(LIBSDL2_DIR)/include/SDL2
INCLUDES = -I$(INCLUDES_DIRECTORY) \
		-I$(INCLUDES_DIRECTORY_LIBFT) \
		-I$(INCLUDES_SDL2)
HEADERS_LIST = wolf3d.h \
	definetextures.h \
	errorout.h
HEADERS = $(addprefix $(INCLUDES_DIRECTORY), $(HEADERS_LIST))

# Основные файлы программы и их пути:
SRC_DIRECTORY = $(CURDIR)/src
SRC_LIST = /main.c \
	/parsing_maps/map_validation.c \
	/parsing_maps/parsing_maps.c \
	/parsing_maps/user_placing.c \
	/raycasting/cast_raysting.c \
	/raycasting/raycasting.c \
	/raycasting/side_determination.c \
	/raycasting/block_rendering.c \
	/color.c \
	/debug_file.c \
	/event_list.c \
	/init_wolf.c \
	/manipulation.c \
	/sdl_help.c \
	/set_button.c \
	/timer/struct_timer.c \
	/texture_loading.c \
	/timer/timer.c

SRC = $(addprefix $(SRC_DIRECTORY), $(SRC_LIST))

# Определение цвета вывода:
GREEN = \033[0;32;1m
RED = \033[0;31;1m
RESET = \033[0m

# Лабуда-бу-даб-даб
.PHONY: all clean fclean re

# Основные правила сборки:
all: $(NAME)

$(NAME): $(SRC) $(HEADERS) $(LIBFT_DIRECTORY) download_res
	@echo "wolf3d: $(GREEN)Компиляция исполняемого файла$(RESET)\n"
	@$(GCC) $(CCFLAGS) $(INCLUDES) $(LIBRARIES_LIBFT) $(LIBRARIES_SDL2) \
	$(OTHERS_FLAGS) $(SRC) -o $(NAME)
	@echo "wolf3d: $(GREEN)Компиляция завершена$(RESET)\n"

$(LIBFT_DIRECTORY):
	@$(MAKE) -C $(LIBFT_DIRECTORY)

download_res:
	@echo "wolf3d: $(GREEN)Подгрузка материалов$(RESET)\n"
	@git clone https://github.com/Kain2250/resourse_of_wolf3d.git $(CURDIR)/resource
	@echo "wolf3d: $(GREEN)Подгрузка материалов завершена$(RESET)\n"

sdl2:
	@echo "SDL2_lib: $(GREEN)Компиляция библиотеки SDL2$(RESET)\n"
	@sh $(CURDIR)/configure.sh
	@echo "SDL2_lib: $(GREEN)Компиляция библиотеки SDL2 завершена$(RESET)\n"

clean:
	@rm -rf $(ALLLIBS)/.deps
	@rm -f $(ALLLIBS)/*.rules
	@rm -f $(ALLLIBS)/*.spec
	@rm -f $(ALLLIBS)/*.cmake
	@rm -f $(ALLLIBS)/*.pc
	@rm -rf $(ALLLIBS)/include/
	@rm -rf $(ALLLIBS)/temp_src
	@echo "$(NAME): $(RED)Объектные и вспомогательные файлы SDL2 удалены$(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIRECTORY) clean

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)Исполняемый файл $(NAME) удален$(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIRECTORY) fclean
	@echo "Libft: $(RED)Библиотека Libft удалена$(RESET)\n"
	# @rm -rf $(LIBSDL2_DIR)
	# @echo "$(NAME): $(RED)Библиотека SDL2 удалена$(RESET)\n"

re:
	@$(MAKE) fclean
	@$(MAKE) all
	