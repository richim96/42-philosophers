# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/22 19:38:06 by rmei              #+#    #+#              #
#    Updated: 2025/05/22 21:54:14 by rmei             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CPPFLAGS = -I./include
CFLAGS = -Wall -Wextra -Werror -D DEBUG_FORMATTING=1 -g
SRC = actions.c init.c main.c monitor. utils.c
SRC := $(addprefix src/, ${SRC})
OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	cc $^ -o $@

%.o: %.c
	cc $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
