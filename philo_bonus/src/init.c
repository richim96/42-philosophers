/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:38:38 by rmei              #+#    #+#             */
/*   Updated: 2025/05/24 20:00:50 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @brief Initializes the data structure
 * @param data Pointer to the data structure
 * @param argc Number of arguments
 * @param argv Array of arguments
 * @return 1 if initialization was successful, 0 otherwise
 */
int ft_init_data(t_data *data, int argc, char **argv)
{
    data->num_philos = ft_atoi(argv[1]);
    if (data->num_philos < 2)
        return (0);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    data->must_eat = -1;
    if (argc == 6)
        data->must_eat = ft_atoi(argv[5]);
    data->num_dead = 0;
    data->start_time = ft_get_time();
    data->philos = malloc(sizeof(t_philo) * data->num_philos);
    if (!data->philos)
        return (0);
    return (1);
}

/**
 * @brief Initializes the semaphores
 * @param data Pointer to the data structure
 * @return 1 if initialization was successful, 0 otherwise
 */
int ft_init_semaphores(t_data *data)
{
    sem_unlink("/forks");
    sem_unlink("/print");
    sem_unlink("/death");
    sem_unlink("/meals");
    data->forks = sem_open("/forks", O_CREAT, 0644, data->num_philos);
    data->print = sem_open("/print", O_CREAT, 0644, 1);
    data->death = sem_open("/death", O_CREAT, 0644, 1);
    data->meals = sem_open("/meals", O_CREAT, 0644, 1);
    if (data->forks == SEM_FAILED || data->print == SEM_FAILED ||
        data->death == SEM_FAILED || data->meals == SEM_FAILED)
        return (0);
    return (1);
}

/**
 * @brief Initializes the philosophers
 * @param data Pointer to the data structure
 * @return 1 if initialization was successful, 0 otherwise
 */
int ft_init_philos(t_data *data)
{
    int i;
    int j;

    i = 0;
    j = 1;
    while (i < data->num_philos)
    {
        data->philos[i].id = j++;
        data->philos[i].times_eaten = 0;
        data->philos[i].last_meal = data->start_time;
        data->philos[i].data = data;
        i++;
    }
    return (1);
}

/**
 * @brief Frees the memory allocated for the philosophers
 * @param data Pointer to the data structure
 */
void ft_philos_memclean(t_data *data)
{
    free(data->philos);
}

/**
 * @brief Cleans up the semaphores
 * @param data Pointer to the data structure
 */
void ft_cleanup_semaphores(t_data *data)
{
    sem_close(data->forks);
    sem_close(data->print);
    sem_close(data->death);
    sem_close(data->meals);
    sem_unlink("/forks");
    sem_unlink("/print");
    sem_unlink("/death");
    sem_unlink("/meals");
}
