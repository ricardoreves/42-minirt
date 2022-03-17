# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/17 18:19:59 by rpinto-r          #+#    #+#              #
#    Updated: 2022/03/17 18:24:43 by rpinto-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### VARIABLES ###
CC         = gcc
CFLAGS     = -Werror -Wextra -Wall
RM         = rm -rf
NORM       = norminette
NAME       = minirt
INC        = ./incs
SRC_DIR    = ./srcs
SRC_NAME   = main.c
SRCS       = $(addprefix $(SRC_DIR)/, $(SRC_NAME))
OBJS       = $(SRCS:.c=.o)
DEBUG_FLAG = -g3 -fsanitize=leak
LIBFT_FLAG = -lft
LIBFT_DIR  = ./libft
LIBFT_INC  = ./libft

### RULES ###
all: $(NAME)

.c.o:
	$(CC) -I $(INC) -I $(LIBFT_INC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(OBJS) $(CFLAGS) $(LIBFT_FLAG) -L $(LIBFT_DIR) -o $(NAME) 

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

run:
	./$(NAME)

norm:
	$(NORM) $(INC) $(SRC_DIR) $(LIBFT_DIR) | grep Error

dev: CFLAGS += $(DEBUG_FLAG)
dev: $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) dev
	$(CC) $(OBJS) $(CFLAGS) $(LIBFT_FLAG) -L $(LIBFT_DIR) -o $(NAME)

valgrind:
	valgrind --leak-check=full ./$(NAME)

.PHONY: all clean fclean re