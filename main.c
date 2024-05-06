/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:07:23 by blebas            #+#    #+#             */
/*   Updated: 2024/05/06 16:30:20 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_digit(char **str)
{
	int	i;
	int	j;

	i = 1;
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
		printf("%sOnly digit or positiv nbr plzzz%s\n", RED, NC);
		return (1);
	}
	while (i < argc)
	{
		if (ft_atol(argv[i]) > INT_MAX)
		{
			printf("%sNO DIGIT SUPERIOR TO INT MAX PLZ%s\n", RED, NC);
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (!check_args(argc, argv))
	{
		parse_input(&table, argv);
		data_init(&table);
		dinner_start(&table);
		//clean(&table);
	}
	return (0);
}
