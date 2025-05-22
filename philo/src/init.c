/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:30:16 by rmei              #+#    #+#             */
/*   Updated: 2025/05/22 23:23:07 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Initializes the data structure with command line arguments
 * @param data Pointer to the data structure to initialize
 * @param argc Number of command line arguments
 * @param argv Array of command line arguments
 * @return 1 on success, 0 on failure
 */
int ft_init_data(t_data *data, int argc, char **argv)
{
    data->num_philos = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    data->must_eat = -1;
    if (argc == 6)
        data->must_eat = ft_atoi(argv[5]);
    data->is_dead = 0;
    data->start_time = ft_get_time();
    data->philos = malloc(sizeof(t_philo) * data->num_philos);
    if (!data->philos)
        return (0);
    return (1);
}

/**
 * @brief Initializes all mutexes for forks and synchronization
 * @param data Pointer to the data structure containing mutexes
 * @return 1 on success, 0 on failure
 */
int ft_init_mutexes(t_data *data)
{
    int i;

    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
    if (!data->forks)
        return (0);
    i = 0;
    while (i < data->num_philos)
    {
        if (pthread_mutex_init(&data->forks[i], NULL))
            return (0);
        i++;
    }
    if (pthread_mutex_init(&data->print, NULL))
        return (0);
    if (pthread_mutex_init(&data->death, NULL))
        return (0);
    return (1);
}

/**
 * @brief Initializes philosopher structures with their initial values
 * @param data Pointer to the data structure containing philosophers
 * @return 1 on success, 0 on failure
 */
int ft_init_philos(t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_philos)
    {
        data->philos[i].id = i + 1;
        data->philos[i].left_fork = i;
        data->philos[i].right_fork = (i + 1) % data->num_philos;
        data->philos[i].times_eaten = 0;
        data->philos[i].last_meal = data->start_time;
        data->philos[i].data = data;
        i++;
    }
    return (1);
}

/**
 * @brief Cleans up all allocated memory and mutexes
 * @param data Pointer to the data structure to clean up
 */
void ft_memclean(t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_philos)
    {
        pthread_mutex_destroy(&data->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&data->print);
    pthread_mutex_destroy(&data->death);
    free(data->forks);
    free(data->philos);
}
