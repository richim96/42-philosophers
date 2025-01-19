/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:25:33 by rmei              #+#    #+#             */
/*   Updated: 2024/09/04 18:25:34 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void ft_start_dinner(t_dinner *d)
{
    printf("Starting dinner with %d philosophers\n", d->number_of_philosophers);
}

int main(int argc, char **argv)
{
    t_dinner *d;

    if (argc < 5 || argc > 6)
        return (ft_error("[ERROR] Invalid number of arguments\n"));
    d = malloc(sizeof(t_dinner));
    if (!d)
        return (ft_error("[ERROR] Malloc failed\n"));
    d->number_of_philosophers = ft_atoi(argv[1]);
    d->time_to_die = ft_atoi(argv[2]);
    d->time_to_eat = ft_atoi(argv[3]);
    d->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        d->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
    else
        d->number_of_times_each_philosopher_must_eat = -1;
    if (d->number_of_philosophers <=1)
        return (ft_error("[ERROR] Philosophers cannot be less than 1\n"));
    if (d->time_to_die <= 0 || d->time_to_eat <= 0 || d->time_to_sleep <= 0)
        return (ft_error("[ERROR] Time arguments cannot be negative\n"));
    ft_print_title();
    ft_start_dinner(d);
    return (0);
}
