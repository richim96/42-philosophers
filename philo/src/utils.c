/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:45:33 by rmei              #+#    #+#             */
/*   Updated: 2025/05/22 23:24:03 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Converts to int the initial portion of a string. The string can begin with
 * an arbitrary amount of white spaces (isspace(3)), followed by a single,
 * optional sign('+' or '-'). Returns the converted value, or 0 on error.
 * @param str String to convert
 * @return Converted integer
 */
int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	sign_count;

	result = 0;
	sign = 1;
	sign_count = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	while (*str == '+' || *str == '-')
	{
		if (++sign_count > 1)
			return (result);
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		result = (result * 10) + (*str++ - '0');
	return (result * sign);
}

/**
 * @brief Writes a string to the given file descriptor
 * @param s String to write
 * @param fd File descriptor
 * @return Number of bytes written
 */
int ft_write_fd(char *s, int fd)
{
    int len;

	if (!s)
		return (ft_write_fd("(null)", fd));
    len = 0;
    while (s[len])
        len++;
    write(fd, s, len);
	return (len);
}

/**
 * @brief Gets the current time in milliseconds
 * @return Current time in milliseconds
 */
long long ft_get_time(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/**
 * @brief Sleeps for the specified time in milliseconds
 * @param time Time to sleep in milliseconds
 */
void ft_usleep(long long time)
{
    long long start;

    start = ft_get_time();
    while (ft_get_time() - start < time)
        usleep(100);
}

/**
 * @brief Prints a message with timestamp and philosopher ID
 * @param philo Pointer to the philosopher structure
 * @param status Status message to print
 */
void ft_print(t_philo *philo, char *status)
{
    pthread_mutex_lock(&philo->data->print);
    if (!philo->data->is_dead)
        printf(
            "%lld %d %s\n",
            ft_get_time() - philo->data->start_time,
            philo->id,
            status
        );
    pthread_mutex_unlock(&philo->data->print);
}

/**
 * @brief Checks if a philosopher has died
 * @param philo Pointer to the philosopher structure
 * @return 1 if philosopher has died, 0 otherwise
 */
int ft_check_death(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->death);
    if (philo->data->is_dead)
    {
        pthread_mutex_unlock(&philo->data->death);
        return (1);
    }
    pthread_mutex_unlock(&philo->data->death);
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

    i = 0;
    while (i < data->num_philos)
    {
        if (data->philos[i].times_eaten < data->must_eat)
            return (0);
        i++;
    }
    return (1);
}
