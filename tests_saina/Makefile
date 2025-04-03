# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/28 16:41:28 by sovincen          #+#    #+#              #
#    Updated: 2025/04/03 17:35:41 by sfraslin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
MLX_FLAGS = -L../git_cub3D/minilibx-linux -lmlx -lX11 -lXext -lm
INCLUDES = -I ./includes/ -I ../git_cub3D/minilibx-linux/ -I ../git_cub3D/libft/
NAME = cub3D
LIB = -L../git_cub3D/libft -lft
LIBFT = ../git_cub3D/libft/libft.a
MINILIBX = ../git_cub3D/minilibx-linux/libmlx.a
SRCS_DIR = srcs/
OBJS_DIR = objs/

FILES = test.c test1.c test2.c\

SRCS = $(addprefix $(SRCS_DIR), $(FILES))

OBJS = $(addprefix $(OBJS_DIR), $(FILES:.c=.o))

vpath %.c $(SRCS_DIR)

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME) $(MLX_FLAGS) $(LIB)

$(OBJS_DIR)%.o : %.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(MINILIBX) : 
	@cd ../git_cub3D/minilibx-linux && ./configure
	@cd ..

$(LIBFT) :
	make --no-print-directory -C ../git_cub3D/libft

clean :
	rm -f  $(OBJS)
	make clean --no-print-directory -C ../git_cub3D/libft

fclean : clean
	rm -f $(NAME)
	make fclean --no-print-directory -C ../git_cub3D/libft

re : fclean all

.PHONY : all clean fclean re
