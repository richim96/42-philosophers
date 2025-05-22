/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:31:59 by rmei              #+#    #+#             */
/*   Updated: 2025/05/22 20:02:13 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int  validate_args(int argc, char **argv)
{
    int i;
    int j;

    if (argc != 5 && argc != 6)
        return (0);
    i = 1;
    while (i < argc)
    {
        j = 0;
        while (argv[i][j])
        {
            if (argv[i][j] < '0' || argv[i][j] > '9')
                return (0);
            j++;
        }
        i++;
    }
    return (1);
}

int main(int argc, char **argv)
{
    t_data  data;
    int     i;

    if (!validate_args(argc, argv))
    {
        printf("Error: Invalid arguments\n");
        return (1);
    }
    if (!ft_init_data(&data, argc, argv))
    {
        printf("Error: Initialization failed\n");
        return (1);
    }
    if (!ft_init_mutexes(&data))
    {
        printf("Error: Mutex initialization failed\n");
        ft_memclean(&data);
        return (1);
    }
    if (!ft_init_philos(&data))
    {
        printf("Error: Philosopher initialization failed\n");
        ft_memclean(&data);
        return (1);
    }
    i = 0;
    while (i < data.num_philos)
    {
        pthread_create(&data.philos[i].thread, NULL, ft_philo_routine, &data.philos[i]);
        i++;
    }
    pthread_create(&data.monitor, NULL, ft_monitor_routine, &data);
    i = 0;
    while (i < data.num_philos)
    {
        pthread_join(data.philos[i].thread, NULL);
        i++;
    }
    pthread_join(data.monitor, NULL);
    ft_memclean(&data);
    return (0);
} 
