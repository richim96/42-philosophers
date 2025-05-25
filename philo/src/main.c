/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:31:59 by rmei              #+#    #+#             */
/*   Updated: 2025/05/25 12:48:05 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int  ft_is_input_valid(int argc, char **argv)
{
    int i;

    if (argc != 5 && argc != 6)
        return (0);
    i = 1;
    while (i < argc)
        if (ft_atoi_strict(argv[i++]) <= 0)
            return (0);
    return (1);
}

static int ft_validate_and_init(t_data *data, int argc, char **argv)
{
    if (!ft_is_input_valid(argc, argv))
    {
        ft_write_fd("[ERROR]: Invalid arguments\n", STDERR_FILENO);
        return(1);
    }
    if (!ft_init_data(data, argc, argv))
    {
        ft_write_fd("[ERROR]: Program init failed\n", STDERR_FILENO);
        return(1);
    }
    if (!ft_init_mutexes(data))
    {
        ft_write_fd("[ERROR]: Mutexes init failed\n", STDERR_FILENO);
        ft_cleanup(data);
        return(1);
    }
    if (!ft_init_philos(data))
    {
        ft_write_fd("[ERROR]: Philosophers init failed\n", STDERR_FILENO);
        ft_cleanup(data);
        return(1);
    }
    return (0);
}

int main(int argc, char **argv)
{
    t_data  data;
    int     i;

    i = ft_validate_and_init(&data, argc, argv);
    if (i == 1)
        return (1);
    while (i < data.num_philos)
    {
        pthread_create(
            &data.philos[i].thread, NULL, ft_philo_routine, &data.philos[i]);
        i++;
    }
    pthread_create(&data.monitor, NULL, ft_monitor_routine, &data);
    i = 0;
    while (i < data.num_philos)
        pthread_join(data.philos[i++].thread, NULL);
    pthread_join(data.monitor, NULL);
    ft_cleanup(&data);
    return (0);
} 
