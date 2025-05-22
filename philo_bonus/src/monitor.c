/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:43:08 by rmei              #+#    #+#             */
/*   Updated: 2025/05/22 22:20:36 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
        philo->data->is_dead = 1;
        sem_post(philo->data->death);
        return (1);
    }
    return (0);
}

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
    data->is_dead = 1;
    sem_post(data->death);
    return (1);
}

void ft_monitor_routine(t_data *data)
{
    int i;
    int status;

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
