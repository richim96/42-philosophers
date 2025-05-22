/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:40:31 by rmei              #+#    #+#             */
/*   Updated: 2025/05/22 22:20:31 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void ft_take_forks(t_philo *philo)
{
    sem_wait(philo->data->forks);
    ft_print_status(philo, "has taken a fork");
    sem_wait(philo->data->forks);
    ft_print_status(philo, "has taken a fork");
}

void ft_drop_forks(t_philo *philo)
{
    sem_post(philo->data->forks);
    sem_post(philo->data->forks);
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

void ft_philo_routine(t_philo *philo)
{
    if (philo->id % 2 == 0)
        ft_usleep(1);
    while (1)
    {
        sem_wait(philo->data->death);
        if (philo->data->is_dead)
        {
            sem_post(philo->data->death);
            break;
        }
        sem_post(philo->data->death);
        ft_take_forks(philo);
        ft_eat(philo);
        ft_drop_forks(philo);
        ft_sleep_think(philo);
    }
} 
