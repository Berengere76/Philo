/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:07:23 by blebas            #+#    #+#             */
/*   Updated: 2024/05/10 09:33:58 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check_digit(char **str)
{
	int	i;
	int	j;

	i = 1;
	if (ft_strlen(str[i]) > 10)
		return (1);
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (!ft_isdigit(str[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_args(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc < 5 || argc > 6)
	{
		printf("%sError, invalid input%s\n", RED, NC);
		return (1);
	}
	if (check_digit(argv))
	{
		printf("%sError, invalid input%s\n", RED, NC);
		return (1);
	}
	while (i < argc)
	{
		if (ft_atol(argv[i]) > INT_MAX)
		{
			printf("%sError, invalid input%s\n", RED, NC);
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	if (!check_args(argc, argv) && !check_args(argc, argv))
	{
		if (philosophers(argc, argv) != 0)
			return (MALLOC_ERROR);
	}
	return (0);
}
