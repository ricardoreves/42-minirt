# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/17 18:19:59 by rpinto-r          #+#    #+#              #
#    Updated: 2022/04/22 15:13:24 by rpinto-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### VARIABLES ###
CC               = gcc
CFLAGS           = -Werror -Wextra -Wall -O3
CDEBUG           = -g3 -fsanitize=address
RM               = rm -rf
NORM             = norminette
NAME             = minirt
SRCS_INC         = ./incs
SRCS             = $(wildcard ./srcs/utils/*.c) \
				   $(wildcard ./srcs/main/*.c) \
				   $(wildcard ./srcs/parsing/*.c) \
				   $(wildcard ./srcs/rt/*.c) \
				   $(wildcard ./srcs/ui/*.c)
OBJS             = $(SRCS:.c=.o)
SCENE		     = ./scenes/mandatory.rt
DEV_SRCS         = $(patsubst %/main.c, %/dev.c, $(SRCS))
DEV_OBJS         = $(DEV_SRCS:.c=.o)

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
	$(CC) -g3 $(OBJS) $(CFLAGS) $(LIBFT_FLAGS) $(LIBMLX_FLAGS) -L $(LIBFT_DIR) -L $(LIBMLX_DIR) -o $(NAME)

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
	$(NORM) $(SRCS_INC) $(SRCS_DIR) $(LIBFT_DIR)

dev: CFLAGS += $(CDEBUG)
dev: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LIBFT_FLAGS) $(LIBMLX_FLAGS) -L $(LIBFT_DIR) -L $(LIBMLX_DIR) -o $(NAME)
	$(MAKE) run

valgrind:
	valgrind --leak-check=full ./$(NAME)

.PHONY: all clean fclean re