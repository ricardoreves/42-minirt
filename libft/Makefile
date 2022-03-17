# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/07 14:49:05 by rpinto-r          #+#    #+#              #
#    Updated: 2022/02/16 07:58:01 by dthalman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COMPILE ###
CC         = gcc
CFLAGS     = -Wall -Wextra -Werror
CDEBUG     = -g3 -fsanitize=address
RM         = rm -rf
AR         = ar -rcs
NORM       = norminette

### FILES ###
AOUT       = a.out
NAME       = libft.a
SRCS       = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c
SRCS_BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJS       = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

ifeq ($(shell uname), Linux)
	DEBUG_FLAG = -g3 -fsanitize=leak
else
	DEBUG_FLAG = -g3 -fsanitize=address
endif

### RULES ###
all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) ${OBJS_BONUS}
	$(AR) $(NAME) $(OBJS) ${OBJS_BONUS}

bonus: ${OBJS} ${OBJS_BONUS}
	$(AR) $(NAME) $(OBJS) ${OBJS_BONUS}

clean:
	$(RM) $(OBJS) ${OBJS_BONUS}

fclean: clean
	$(RM) $(NAME) $(AOUT)

re: fclean all

dev: CFLAGS += $(DEBUG_FLAG)
dev: $(OBJS) ${OBJS_BONUS}
	$(AR) $(NAME) $(OBJS) ${OBJS_BONUS}

norm:
	$(NORM)

.PHONY: all clean fclean re
