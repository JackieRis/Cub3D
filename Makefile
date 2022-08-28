# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnguyen- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/02 13:26:21 by tnguyen-          #+#    #+#              #
#    Updated: 2022/05/06 17:53:08 by tnguyen-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D

SRCS	= main.c function.c utils.c parsing.c get_next_line.c get_next_line_utils.c \
	mapping.c ft_split.c color.c display.c draw.c dda.c load_textures.c dda2.c \
	event.c event_hook.c move.c clear.c init.c image.c checks.c

OBJ	= ${SRCS:.c=.o}

MAKEFILEV = Makefile

CC = gcc

FLAGS = -Wall -Werror -Wextra -I. -O3 #-fsanitize=address -g3

LIB = libmlx.dylib
LIB_CHECK = mlx/libmlx.dylib

all: ${NAME}

%.o: %.c $(MAKEFILEV) cub3d.h get_next_line.h mlx_input.h
	$(CC) ${FLAGS} -Imlx -c $< -o $@

${NAME}: $(MAKEFILEV) $(LIB) ${OBJ} 
	$(CC) ${FLAGS} $(OBJ) -framework OpenGL -framework AppKit -o $(NAME) mlx/libmlx.dylib

${LIB}: $(LIB_CHECK)
	cp $(LIB_CHECK) .

$(LIB_CHECK):
	make -C mlx

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all
