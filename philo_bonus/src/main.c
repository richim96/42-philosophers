/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:43:38 by rmei              #+#    #+#             */
/*   Updated: 2025/05/22 23:03:05 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int  ft_validate_args(int argc, char **argv)
{
    int i;
    int j;
    int num;

    if (argc != 5 && argc != 6)
        return (0);
    i = 1;
    while (i < argc)
    {
        j = 0;
        while (argv[i][j])
        {
            if (argv[i][j] < '0' || argv[i][j] > '9')
                return (0);
            j++;
        }
        num = ft_atoi(argv[i]);
        if (num <= 0)
            return (0);
        i++;
    }
    return (1);
}

static void ft_validate_and_init(t_data *data, int argc, char **argv)
{
    if (!ft_validate_args(argc, argv))
    {
        ft_write_fd("[ERROR]: Invalid arguments\n", STDERR_FILENO);
        exit(1);
    }
    if (!ft_init_data(data, argc, argv))
    {
        ft_write_fd("[ERROR]: Program init failed\n", STDERR_FILENO);
        exit(1);
    }
    if (!ft_init_semaphores(data))
    {
        ft_write_fd("[ERROR]: Semaphores init failed\n", STDERR_FILENO);
        ft_philos_memclean(data);
        exit(1);
    }
    if (!ft_init_philos(data))
    {
        ft_write_fd("[ERROR]: Philosophers init failed\n", STDERR_FILENO);
        ft_cleanup_semaphores(data);
        ft_philos_memclean(data);
        exit(1);
    }
}

int main(int argc, char **argv)
{
    t_data  data;
    int     i;

    ft_validate_and_init(&data, argc, argv);
    i = 0;
    while (i < data.num_philos)
    {
        data.philos[i].pid = fork();
        if (data.philos[i].pid == 0)
        {
            ft_philo_routine(&data.philos[i]);
            exit(0);
        }
        i++;
    }
    ft_monitor_routine(&data);
    i = 0;
    while (i < data.num_philos)
    {
        kill(data.philos[i].pid, SIGKILL);
        i++;
    }
    ft_cleanup_semaphores(&data);
    ft_philos_memclean(&data);
    return (0);
} 
