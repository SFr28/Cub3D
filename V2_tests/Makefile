# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/28 16:41:28 by sovincen          #+#    #+#              #
#    Updated: 2025/04/09 13:41:06 by sfraslin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
MLX_FLAGS = -L../git_cub3D/minilibx-linux -lmlx -lX11 -lXext -lm
INCLUDES = -I ./includes/ -I ../git_cub3D/minilibx-linux/ -I ../git_cub3D/libft/
NAME = cub3D_test
LIB = -L../git_cub3D/libft -lft
LIBFT = ../git_cub3D/libft/libft.a
MINILIBX = ../git_cub3D/minilibx-linux/libmlx.a
SRCS_DIR = srcs/
OBJS_DIR = objs/

FILES = test_V2_1.c test_init_V2.c ft_image_test.c ft_keys_test.c draw_utils_test.c

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
