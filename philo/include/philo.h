/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:32:03 by rmei              #+#    #+#             */
/*   Updated: 2025/05/25 13:19:16 by rmei             ###   ########.fr       */
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

/**
 * @brief A philosopher.
 * @param id           (int) Philosopher's id
 * @param left_fork    (int) Index of the fork to the left
 * @param right_fork   (int) Index of the fork to the right
 * @param times_eaten  (int) Number of times the philosopher has eaten
 * @param last_meal    (long long) Timestamp of the philosopher's last meal
 * @param thread       (pthread_t) Thread handle for the philosopher's execution
 * @param data         (t_data *) Pointer to the shared data structure
 */
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

/**
 * @brief Shared data.
 * @param num_philos    (int) Total number of philosophers
 * @param time_to_die   (int) Time in ms after which a philo dies if not eating
 * @param time_to_eat   (int) Time in ms it takes for a philo to eat
 * @param time_to_sleep (int) Time in ms it takes for a philo to sleep
 * @param must_eat      (int) Number of times each philo must eat - optional
 * @param terminate     (int) Flag indicating if the simulation should end
 * @param start_time    (long long) Timestamp when the simulation started
 * @param philos        (t_philo *) Array of philosopher structures
 * @param forks         (pthread_mutex_t *) Array of mutexes representing forks
 * @param print_death   (pthread_mutex_t) Mutex for synchronized death message
 * @param death         (pthread_mutex_t) Mutex for death checking
 * @param monitor       (pthread_t) Thread handle for the monitor thread
 */
typedef struct s_data
{
    int             num_philos;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             must_eat;
    int             terminate;
    long long       start_time;
    t_philo         *philos;
    pthread_mutex_t *forks;
    pthread_mutex_t print_death;
    pthread_mutex_t death;
    pthread_t       monitor;
} t_data;

// Initialization and cleanup functions
int         ft_init_data(t_data *data, int argc, char **argv);
int         ft_init_philos(t_data *data);
int         ft_init_mutexes(t_data *data);
void        ft_cleanup(t_data *data);

// Philosopher actions
void        *ft_philo_routine(void *arg);
void        ft_take_forks(t_philo *philo);
void        ft_drop_forks(t_philo *philo);
void        ft_eat(t_philo *philo);
void        ft_sleep_think(t_philo *philo);

// Monitor functions
void        *ft_monitor_routine(void *arg);
int         ft_check_death(t_data *data);
int         ft_check_meals(t_data *data);

// Utility functions
int         ft_atoi_strict(const char *str);
int         ft_write_fd(char *s, int fd);
void        ft_usleep(long long time);
long long   ft_get_time(void);
void        ft_print_status(t_philo *philo, char *status);

#endif 
