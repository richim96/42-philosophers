/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:31:54 by rmei              #+#    #+#             */
/*   Updated: 2025/05/25 13:51:25 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Main routine for each philosopher thread.
 * @param philo Pointer to the philosopher structure
 * @return *NULL
 */
void *ft_philo_routine(void *philo_ptr)
{
    t_philo *philo;

    philo = (t_philo *)philo_ptr;
    if (philo->id % 2 == 0)
        ft_usleep(1);
    while (1)
    {
        pthread_mutex_lock(&philo->data->death);
        if (philo->data->terminate)
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

/**
 * @brief Takes two forks for a philosopher.
 * @param philo Pointer to the philosopher structure
 */
void ft_take_forks(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
    ft_print_status(philo, "has taken a fork");
    if (philo->left_fork == philo->right_fork)
    {
        ft_usleep(philo->data->time_to_die + 1);
        return;
    }
    pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
    ft_print_status(philo, "has taken a fork");
}

/**
 * @brief Drops two forks for a philosopher
 * @param philo Pointer to the philosopher structure
 */
void ft_drop_forks(t_philo *philo)
{
    pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
    pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

/**
 * @brief Makes a philosopher eat
 * @param philo Pointer to the philosopher structure
 */
void ft_eat(t_philo *philo)
{
    ft_print_status(philo, "is eating");
    philo->last_meal = ft_get_time();
    philo->times_eaten++;
    ft_usleep(philo->data->time_to_eat);
}

/**
 * @brief Makes a philosopher sleep and think
 * @param philo Pointer to the philosopher structure
 */
void ft_sleep_think(t_philo *philo)
{
    ft_print_status(philo, "is sleeping");
    ft_usleep(philo->data->time_to_sleep);
    ft_print_status(philo, "is thinking");
}
