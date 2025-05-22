# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/22 19:38:06 by rmei              #+#    #+#              #
#    Updated: 2025/05/22 19:59:47 by rmei             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CPPFLAGS = -I./include
CFLAGS = -Wall -Wextra -Werror -g
SRC = philo.c init.c philo_actions.c monitor.c utils.c
SRC := $(addprefix src/, ${SRC})
OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	cc $^ -o $@

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
