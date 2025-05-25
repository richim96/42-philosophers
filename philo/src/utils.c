/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:45:33 by rmei              #+#    #+#             */
/*   Updated: 2025/05/25 13:31:37 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Converts a valid numerical string (unsigned) to an integer. 
 * @param str String to convert
 * @return Converted integer - 0 on error
 */
int	ft_atoi_strict(const char *str)
{
	int	result;
	
	result = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		result = (result * 10) + (*str - '0');
		str++;
	}
	return (result);
}

/**
 * @brief Writes a string to the given file descriptor.
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
 * @brief Gets the current time in milliseconds.
 * @return Current time in milliseconds
 */
long long ft_get_time(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/**	
 * @brief Sleeps for the specified time in milliseconds.
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
 * @brief Prints a message with timestamp and philosopher ID.
 * @param philo Pointer to the philosopher structure
 * @param status Status message to print
 */
void ft_print_status(t_philo *philo, char *status)
{
    pthread_mutex_lock(&philo->data->print_death);
    if (!philo->data->terminate)
        printf(
            "%lld %d %s\n",
            ft_get_time() - philo->data->start_time,
            philo->id,
            status
        );
    pthread_mutex_unlock(&philo->data->print_death);
}
