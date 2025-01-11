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

int main(int argc, char **argv)
{
    int n_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;

    if (argc != 5)
        return (ft_write_error("[ERROR] Invalid number of arguments\n"));
    n_philosophers = ft_atoi(argv[1]);
    time_to_die = ft_atoi(argv[2]);
    time_to_eat = ft_atoi(argv[3]);
    time_to_sleep = ft_atoi(argv[4]);
    if (n_philosophers <=1)
        return (ft_write_error("[ERROR] Philosophers cannot be less than 1\n"));
    if (time_to_die <= 0 || time_to_eat <= 0 || time_to_sleep <= 0)
        return (ft_write_error("[ERROR] Time arguments cannot be negative\n"));
    printf("Number of philosophers: %d\n", n_philosophers);
    printf("Time to die: %d\n", time_to_die);
    printf("Time to eat: %d\n", time_to_eat);
    printf("Time to sleep: %d\n", time_to_sleep);
    return (0);
}
