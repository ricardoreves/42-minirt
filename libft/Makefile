# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/07 14:49:05 by rpinto-r          #+#    #+#              #
#    Updated: 2022/03/17 20:15:09 by rpinto-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### VARIABLES ###
CC              = gcc
CFLAGS          = -Wall -Wextra -Werror
CDEBUG          = -g3 -fsanitize=address
RM              = rm -rf
AR              = ar -rcs
NORM            = norminette
NAME            = libft.a
SRCS_INC        = ./incs
SRCS_DIR        = ./srcs
SRCS_NAME       = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c
SRCS            = $(addprefix $(SRCS_DIR)/, $(SRCS_NAME))
OBJS            = $(SRCS:.c=.o)
BONUS_SRCS_NAME = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
BONUS_SRCS      = $(addprefix $(SRCS_DIR)/, $(BONUS_SRCS_NAME))
BONUS_OBJS      = $(BONUS_SRCS:.c=.o)

### RULES ###
all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -I $(SRCS_INC) -c $< -o $@

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

bonus: ${OBJS} ${BONUS_OBJS}
	$(AR) $(NAME) $(OBJS) ${BONUS_OBJS}

clean:
	$(RM) $(OBJS) ${BONUS_OBJS}

fclean: clean
	$(RM) $(NAME)

re: fclean all

dev: CFLAGS += $(CDEBUG)
dev: $(OBJS) ${BONUS_OBJS}
	$(AR) $(NAME) $(OBJS) ${BONUS_OBJS}

norm:
	$(NORM)

.PHONY: all clean fclean re
