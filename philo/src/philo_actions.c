/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:31:54 by rmei              #+#    #+#             */
/*   Updated: 2025/05/22 19:59:53 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_print_status(t_philo *philo, char *status)
{
    pthread_mutex_lock(&philo->data->print);
    if (!philo->data->is_dead)
        printf("%lld %d %s\n", ft_get_time() - philo->data->start_time, philo->id, status);
    pthread_mutex_unlock(&philo->data->print);
}

void ft_take_forks(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
    ft_print_status(philo, "has taken a fork");
    pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
    ft_print_status(philo, "has taken a fork");
}

void ft_drop_forks(t_philo *philo)
{
    pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
    pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

void ft_eat(t_philo *philo)
{
    ft_print_status(philo, "is eating");
    philo->last_meal = ft_get_time();
    philo->times_eaten++;
    ft_usleep(philo->data->time_to_eat);
}

void ft_sleep_think(t_philo *philo)
{
    ft_print_status(philo, "is sleeping");
    ft_usleep(philo->data->time_to_sleep);
    ft_print_status(philo, "is thinking");
}

void *ft_philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->id % 2 == 0)
        ft_usleep(1);
    while (1)
    {
        pthread_mutex_lock(&philo->data->death);
        if (philo->data->is_dead)
        {
            pthread_mutex_unlock(&philo->data->death);
            break;
        }
        pthread_mutex_unlock(&philo->data->death);
        ft_take_forks(philo);
        ft_eat(philo);
        ft_drop_forks(philo);
        ft_sleep_think(philo);
    }
    return (NULL);
} 
