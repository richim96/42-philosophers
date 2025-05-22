/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:31:52 by rmei              #+#    #+#             */
/*   Updated: 2025/05/22 22:13:03 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
            data->is_dead = 1;
            pthread_mutex_unlock(&data->death);
            return (1);
        }
        i++;
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
    pthread_mutex_lock(&data->death);
    data->is_dead = 1;
    pthread_mutex_unlock(&data->death);
    return (1);
}

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
