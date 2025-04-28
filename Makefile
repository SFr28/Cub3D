# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/28 16:41:28 by sovincen          #+#    #+#              #
#    Updated: 2025/04/23 14:30:01 by sovincen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP -g3
MLX_FLAGS = -Lminilibx-linux -lmlx -lX11 -lXext -lm
INCLUDES = -I ./includes/ -I ./minilibx-linux/ -I ./libft/
NAME = cub3D
LIB = -Llibft -lft
LIBFT = ./libft/libft.a
MINILIBX = ./minilibx-linux/libmlx.a
SRCS_DIR = srcs/
OBJS_DIR = objs/

FILES = main.c \
		draw.c hooks.c map.c player.c raycasting.c raycasting2.c\
		init_window.c init.c \
		parse_map.c element_check.c player_parsing.c \
		parsing_gameinfo.c error_parsing.c parsing_texture.c path_texture.c\
		clean.c parsing_utils.c image_utils.c

SRCS = $(addprefix $(SRCS_DIR), $(FILES))

OBJS = $(addprefix $(OBJS_DIR), $(FILES:.c=.o))
DEPS = $(OBJS:.o=.d)

vpath %.c $(SRCS_DIR) $(SRCS_DIR)utils $(SRCS_DIR)parsing $(SRCS_DIR)init \
$(SRCS_DIR)exec

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME) $(MLX_FLAGS) $(LIB)

$(OBJS_DIR)%.o : %.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(MINILIBX) : 
	@cd minilibx-linux && ./configure
	@cd ..

$(LIBFT) :
	make --no-print-directory -C ./libft

clean :
	rm -f  $(OBJS)
	make clean --no-print-directory -C ./libft

fclean : clean
	rm -f $(NAME)
	make fclean --no-print-directory -C ./libft

re : fclean all

.PHONY : all clean fclean re

-include $(DEPS)
