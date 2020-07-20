# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/21 19:14:26 by kain2250          #+#    #+#              #
#    Updated: 2020/07/20 12:48:14 by bdrinkin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Определение системных команд
NAME = wolf3d

# Флаги компиляции:
GCC = gcc
CCFLAGS = -Wall -Wextra -Werror
FLAGS = -O3
THREADS_FLAGS = -lpthread
OTHERS_FLAGS = -lm
SDL2_FLAGS = -lSDL2_ttf -lSDL2_image -lSDL2_mixer -lSDL2 -liconv -Wl,-framework,CoreAudio -Wl,-framework,AudioToolbox -Wl,-framework,ForceFeedback -lobjc -Wl,-framework,CoreVideo -Wl,-framework,Cocoa -Wl,-framework,Carbon -Wl,-framework,IOKit -Wl,-weak_framework,QuartzCore -Wl,-weak_framework,Metal

# Список библиотек и их пути:
ALLLIBS = $(CURDIR)/allLibs/
LIBFT_DIRECTORY = $(ALLLIBS)libft/
LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBSDL2_DIR = $(ALLLIBS)libsdl2/
LIBSDL2 = $(LIBSDL2_DIR)lib/

# Флаги для сборки библиотек
LIBRARIES_LIBFT = -L$(LIBFT_DIRECTORY) -lft
LIBRARIES_SDL_U = -L $(LIBSDL2) $(THREADS_FLAGS) $(OTHERS_FLAGS) $(SDL2_FLAGS)
				#$$(sdl2-config --cflags --libs)

# Заголовочные файлы и их пути:
INCLUDES_DIRECTORY = $(CURDIR)/includes/
INCLUDES_DIRECTORY_LIBFT = $(LIBFT_DIRECTORY)includes/
INCLUDES_SDL2 = $(LIBSDL2_DIR)include/SDL2/
INCLUDES = -I $(INCLUDES_DIRECTORY) \
		-I $(INCLUDES_DIRECTORY_LIBFT) \
		-I $(INCLUDES_SDL2)
	
# Основные файлы программы и их пути:
SRC_DIRECTORY = $(CURDIR)/src/
SRC_LIST = *.c

SRC = $(addprefix $(SRC_DIRECTORY), $(SRC_LIST))

# Объектные файлы и их пути:
OBJECTS = $(addprefix $(OBJ_DIR), $(OBJ_LIST))
OBJ_DIR = objects/
OBJ_LIST = $(patsubst %.c, %.o, $(SRC_LIST))

# Определение цвета вывода:
GREEN = \033[0;32;1m
RED = \033[0;31;1m
RESET = \033[0m

# Лабуда-бу-даб-даб
.PHONY: all clean fclean re

# Основные правила сборки:
all: builds

builds:
	@gcc -Wall -Wextra -Werror -Iincludes -IallLibs/libft/includes -IallLibs/SDL2/include/SDL2 -LallLibs/libft -lft -LallLibs/SDL2/lib -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf src/*.c -o wolf3d

clean:
	@echo "$(NAME): $(RED)Объектные файлы удалены$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME)Удалено$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all
	