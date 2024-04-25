/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:10:56 by blebas            #+#    #+#             */
/*   Updated: 2024/04/22 15:26:57 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(char *nptr)
{
	long	res;
	int		j;
	int		k;

	res = 0;
	j = 0;
	k = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (nptr[0] == '-')
		k = -1;
	if (*nptr == '-' || *nptr == '+')
	{
		j++;
		nptr++;
		if (j >= 2)
			return (0);
	}
	while ((*nptr != '\0') && (*nptr >= '0' && *nptr <= '9'))
	{
		res = res * 10 + (*nptr - '0');
		nptr++;
	}
	return (res * k);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
