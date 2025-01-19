/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:25:23 by rmei              #+#    #+#             */
/*   Updated: 2024/09/04 18:25:25 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* STRUCTS */

typedef struct s_dinner
{
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
}   t_dinner;


/* FUNCTIONS */

int	ft_atoi(const char *nptr);
int	ft_error(const char *message);
int	ft_strlen(const char *str);

void ft_print_title(void);

#endif
