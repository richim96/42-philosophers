/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:32:03 by rmei              #+#    #+#             */
/*   Updated: 2025/05/22 20:01:10 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_philo
{
    int             id;
    int             left_fork;
    int             right_fork;
    int             times_eaten;
    long long       last_meal;
    pthread_t       thread;
    struct s_data   *data;
} t_philo;

typedef struct s_data
{
    int             num_philos;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             must_eat;
    int             is_dead;
    long long       start_time;
    t_philo         *philos;
    pthread_mutex_t *forks;
    pthread_mutex_t print;
    pthread_mutex_t death;
    pthread_t       monitor;
} t_data;

// Utility functions
int         ft_atoi(const char *str);
void        ft_usleep(long long time);
long long   ft_get_time(void);
void        ft_print_status(t_philo *philo, char *status);

// Initialization functions
int         ft_init_data(t_data *data, int argc, char **argv);
int         ft_init_philos(t_data *data);
int         ft_init_mutexes(t_data *data);

// Philosopher functions
void        *ft_philo_routine(void *arg);
void        ft_take_forks(t_philo *philo);
void        ft_drop_forks(t_philo *philo);
void        ft_eat(t_philo *philo);
void        ft_sleep_think(t_philo *philo);

// Monitor functions
void        *ft_monitor_routine(void *arg);
int         ft_check_death(t_data *data);
int         ft_check_meals(t_data *data);

// Cleanup functions
void        ft_memclean(t_data *data);

#endif 
