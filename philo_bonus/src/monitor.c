/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:43:08 by rmei              #+#    #+#             */
/*   Updated: 2025/05/24 16:35:23 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @brief Checks if a philosopher has died
 * @param philo Pointer to the philosopher structure
 * @return 1 if philosopher has died, 0 otherwise
 */
int ft_check_death(t_philo *philo)
{
    long long now;

    now = ft_get_time();
    if (now - philo->last_meal >= philo->data->time_to_die)
    {
        sem_wait(philo->data->print);
        printf("%lld %d died\n", now - philo->data->start_time, philo->id);
        sem_post(philo->data->print);
        sem_wait(philo->data->death);
        philo->data->num_dead = 1;
        sem_post(philo->data->death);
        return (1);
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
    sem_wait(data->death);
    data->num_dead = 1;
    sem_post(data->death);
    return (1);
}

/**
 * @brief Monitors the philosophers and checks for death or meals
 * @param data Pointer to the data structure
 * @return NULL
 */
void ft_monitor_routine(t_data *data)
{
    int i;

    while (1)
    {
        i = 0;
        while (i < data->num_philos)
        {
            if (ft_check_death(&data->philos[i]))
                return;
            i++;
        }
        if (ft_check_meals(data))
            return;
        usleep(1000);
    }
} 
