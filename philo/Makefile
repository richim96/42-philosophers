# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: riccardomei <riccardomei@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/04 18:25:01 by rmei              #+#    #+#              #
#    Updated: 2025/01/11 18:36:29 by riccardomei      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#### -- VARIABLES -- ####
# Utilities
UTILS_SRC = ft_atoi.c ft_write_error.c
UTILS_SRC := $(addprefix src/lib_utils/, ${UTILS_SRC})

# Philo
PHILO_SRC = main.c
PHILO_SRC := $(addprefix src/, ${PHILO_SRC})
PHILO_SRC += $(UTILS_SRC)
PHILO_OBJS = $(PHILO_SRC:%.c=%.o)
NAME = philo

# Compiler and linker flags
CPPFLAGS = -I./include
CFLAGS = -Wall -Werror -Wextra -g

#### -- RULES -- ####	
all: $(NAME)

# bonus: $() 

# Create executables
$(NAME): $(PHILO_OBJS)
	cc $^ -o $@
	
%.o: %.c
	cc $(CPPFLAGS) $(CFLAGS) -c $< -o $@
	
# Manage object files and executables #
clean:
	rm -f $(PHILO_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all # bonus

.PHONY: all clean fclean re
