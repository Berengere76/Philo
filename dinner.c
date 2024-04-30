/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:44:14 by blebas            #+#    #+#             */
/*   Updated: 2024/04/30 18:43:55 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;

	wait_all_threads(philo->table);

	return (NULL);
}

void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (table->nbr_limit_meals == 0)
		return ;
	else if (table->philo_nbr == 1)
		return ;
	else
	{
		while (++i < table->philo_nbr)
			pthread_create(table->philos[i].thread_id, NULL, dinner_simulation,
				&table->philos[i]);
	}
	table->start_simulation = gettime();
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
}
