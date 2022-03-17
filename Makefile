# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/17 18:19:59 by rpinto-r          #+#    #+#              #
#    Updated: 2022/03/17 21:15:09 by rpinto-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### VARIABLES ###
CC          = gcc
CFLAGS      = -Werror -Wextra -Wall
CDEBUG      = -g3 -fsanitize=leak
RM          = rm -rf
NORM        = norminette
NAME        = minirt
SRCS_INC    = ./incs
SRCS_DIR    = ./srcs
SRCS_NAME   = main.c
SRCS        = $(addprefix $(SRCS_DIR)/, $(SRCS_NAME))
OBJS        = $(SRCS:.c=.o)
LIBFT_FLAG  = -lft
LIBFT_DIR   = ./libft
LIBFT_INC   = ./libft/incs
LIBGNL_FLAG = -lgnl
LIBGNL_DIR  = ./libgnl
LIBGNL_INC  = ./libgnl/incs

### RULES ###
all: $(NAME)

.c.o:
	$(CC) -I $(SRCS_INC) -I $(LIBFT_INC) -I $(LIBGNL_INC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(LIBGNL_DIR)
	$(CC) $(OBJS) $(CFLAGS) $(LIBFT_FLAG) $(LIBGNL_FLAG) -L $(LIBFT_DIR) -L $(LIBGNL_DIR) -o $(NAME) 

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

dev: CFLAGS += $(CDEBUG)
    re: fclean all

run:
	./$(NAME)

norm:
	$(NORM) $(INC) $(SRCS_DIR) $(LIBFT_DIR) | grep Error

dev: $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) dev
	$(MAKE) -C $(LIBGNL_DIR) dev
	$(CC) $(OBJS) $(CFLAGS) $(LIBFT_FLAG) $(LIBGNL_FLAG) -L $(LIBFT_DIR) -L $(LIBGNL_DIR) -o $(NAME)
	$(MAKE) run

valgrind:
	valgrind --leak-check=full ./$(NAME)

.PHONY: all clean fclean re