/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riccardomei <riccardomei@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:30:59 by riccardomei       #+#    #+#             */
/*   Updated: 2025/01/11 18:38:29 by riccardomei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/* Returns the length of a string */
int ft_strlen(const char *str)
{
    int len;

    len = 0;
    while (str[len])
        len++;
    return (len);
}

/* Writes to standard error and returns error */
int ft_write_error(const char *message)
{
    write(2, message, ft_strlen(message));
    return (1);
}
