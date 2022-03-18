# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/17 18:19:59 by rpinto-r          #+#    #+#              #
#    Updated: 2022/03/18 03:44:52 by rpinto-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### VARIABLES ###
CC               = gcc
CFLAGS           = -Werror -Wextra -Wall
CDEBUG           = -g3 -fsanitize=address
RM               = rm -rf
NORM             = norminette
NAME             = minirt
SRCS_INC         = ./incs
SRCS_DIR         = ./srcs
SRCS_NAME        = main.c window.c image.c keyboard.c parsing.c 
SRCS             = $(addprefix $(SRCS_DIR)/, $(SRCS_NAME))
OBJS             = $(SRCS:.c=.o)
SCENE		     = ./scenes/mandatory.rt


### LIBRARIES ###
LIBFT_FLAGS      = -lft
LIBFT_DIR        = ./libft
LIBFT_INC        = ./libft/includes
ifeq ($(shell uname), Linux)
	LIBMLX_DIR   = ./libmlx/linux
	LIBMLX_INC   = ./libmlx/linux
	LIBMLX_FLAGS = -lmlx -lXext -lX11 -lm -lz
else
	LIBMLX_DIR   = ./libmlx/macos
	LIBMLX_INC   = ./libmlx/macos
	LIBMLX_FLAGS = -lmlx -framework openGL -framework AppKit
endif


### RULES ###
all: $(NAME)

.c.o:
	$(CC) -I $(SRCS_INC) -I $(LIBFT_INC) -I $(LIBMLX_INC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(LIBMLX_DIR)
	$(CC) $(OBJS) $(CFLAGS) $(LIBFT_FLAGS) $(LIBMLX_FLAGS) -L $(LIBFT_DIR) -L $(LIBMLX_DIR) -o $(NAME)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(LIBMLX_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

run:
	./$(NAME) $(SCENE)

norm:
	$(NORM) $(SRCS_INC) $(SRCS_DIR) $(LIBFT_DIR) | grep Error

dev: CFLAGS += $(CDEBUG)
dev: $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) dev
	$(MAKE) -C $(LIBMLX_DIR)
	$(CC) $(OBJS) $(CFLAGS) $(LIBFT_FLAGS) $(LIBMLX_FLAGS) -L $(LIBFT_DIR) -L $(LIBMLX_DIR) -o $(NAME)

valgrind:
	valgrind --leak-check=full ./$(NAME)

.PHONY: all clean fclean re