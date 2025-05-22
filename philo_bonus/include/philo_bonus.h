/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:43:44 by rmei              #+#    #+#             */
/*   Updated: 2025/05/22 22:54:33 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/wait.h>

typedef struct s_philo
{
    int             id;
    int             times_eaten;
    long long       last_meal;
    pid_t           pid;
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
    sem_t           *forks;
    sem_t           *print;
    sem_t           *death;
    sem_t           *meals;
} t_data;

// Utility functions
int         ft_atoi(const char *str);
int         ft_write_fd(char *s, int fd);
void        ft_usleep(long long time);
long long   ft_get_time(void);
void        ft_print_status(t_philo *philo, char *status);

// Initialization and cleanup functions
int         ft_init_data(t_data *data, int argc, char **argv);
int         ft_init_philos(t_data *data);
int         ft_init_semaphores(t_data *data);
void        ft_philos_memclean(t_data *data);
void        ft_cleanup_semaphores(t_data *data);

// Philosopher actions
void        ft_philo_routine(t_philo *philo);
void        ft_take_forks(t_philo *philo);
void        ft_drop_forks(t_philo *philo);
void        ft_eat(t_philo *philo);
void        ft_sleep_think(t_philo *philo);

// Monitor functions
int         ft_check_death(t_philo *philo);
int         ft_check_meals(t_data *data);
void        ft_monitor_routine(t_data *data);

#endif 
