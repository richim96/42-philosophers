/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:31:52 by rmei              #+#    #+#             */
/*   Updated: 2025/05/24 16:35:23 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Checks if a philosopher has died
 * @param philo Pointer to the philosopher structure
 * @return 1 if philosopher has died, 0 otherwise
 */
int ft_check_death(t_data *data)
{
    int i;
    long long now;

    i = 0;
    while (i < data->num_philos)
    {
        now = ft_get_time();
        if (now - data->philos[i].last_meal >= data->time_to_die)
        {
            pthread_mutex_lock(&data->print);
            printf("%lld %d died\n", now - data->start_time, data->philos[i].id);
            pthread_mutex_unlock(&data->print);
            pthread_mutex_lock(&data->death);
            data->num_dead = 1;
            pthread_mutex_unlock(&data->death);
            return (1);
        }
        i++;
    }
    return (0);
}

/**
 * @brief Checks if all philosophers have eaten the required number of times
 * @param data Pointer to the data structure
 * @return 1 if all philosophers have eaten enough, 0 otherwise
 */
int ft_check_meals(t_data *data)
{
    int i;

    if (data->must_eat == -1)
        return (0);
    i = 0;
    while (i < data->num_philos)
    {
        if (data->philos[i].times_eaten < data->must_eat)
            return (0);
        i++;
    }
    pthread_mutex_lock(&data->death);
    data->num_dead = 1;
    pthread_mutex_unlock(&data->death);
    return (1);
}

/**
 * @brief Monitors the philosophers and checks for death or meals
 * @param arg Pointer to the data structure
 * @return NULL
 */
void *ft_monitor_routine(void *arg)
{
    t_data *data;

    data = (t_data *)arg;
    while (1)
    {
        if (ft_check_death(data) || ft_check_meals(data))
            break;
        usleep(1000);
    }
    return (NULL);
} 
