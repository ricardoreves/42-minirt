# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/04 10:12:36 by dthalman          #+#    #+#              #
#    Updated: 2022/03/17 20:29:20 by rpinto-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### VARIABLES ###
CC         = gcc
CDEBUG     = -g3 -fsanitize=address
CFLAGS     = -Werror -Wextra -Wall
NORM       = norminette
AR         = ar -rcs
RM         = rm -rf
NAME       = libgnl.a
SRCS_INC   = ./incs
SRCS_DIR   = ./srcs
SRCS_NAME  = get_next_line.c get_next_line_utils.c 
SRCS       = $(addprefix $(SRCS_DIR)/, $(SRCS_NAME))
OBJS       = $(SRCS:.c=.o)

### RULES ###
all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) $(SRCS_INC) -c $< -o $@

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

dev: CFLAGS += $(CDEBUG)
dev: $(OBJS)
	$(AR) $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

norm:
	$(NORM)

.PHONY: all clean fclean re dev
