# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/03 19:39:23 by bgoncalv          #+#    #+#              #
#    Updated: 2022/01/29 15:28:25 by bgoncalv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

INCLUDES	= -I includes/

SRCS		=	$(wildcard dlst/*) \
				$(wildcard ftc/*) \
				$(wildcard gnl/*) \
				$(wildcard lst/*) \
				$(wildcard math/*) \
				$(wildcard printf/*) \
				$(wildcard sort/*) \
				$(wildcard utils/*)

OBJS		= ${SRCS:.c=.o}

RM			= rm -f

_BLUE=\e[34m
_PURPLE=\e[35m
_CYAN=\e[36m
_END=\e[0m

%.o: %.c
			@printf "Libft object : $(_BLUE)%-33.33s\r$(_END)" $@
			@${CC} ${CFLAGS} $(INCLUDES) -c $< -o $@

$(NAME):	$(OBJS)
			@printf "\nLibft Objects	[$(_BLUE)✓$(_END)]\n"
			@ar rc $(NAME) $(OBJS)
			@ranlib $(NAME)
			@printf "Libft		[$(_BLUE)✓$(_END)]\n"

all:		$(NAME)

re:			fclean $(NAME)

clean:
			@$(RM) *.o */*.o
			@printf "$(_PURPLE)libft object	deleted$(_END)\n"

fclean:		clean
			@$(RM) $(NAME)
			@printf "$(_PURPLE)libft		deleted$(_END)\n"

.PHONY:		all re clean fclean