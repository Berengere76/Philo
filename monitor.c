/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:04:42 by blebas            #+#    #+#             */
/*   Updated: 2024/05/07 12:27:14 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;

	if (philo->full)
		return (false);
	pthread_mutex_lock(&philo->philo_mutex);
	elapsed = gettime() - philo->last_meal_time;
	t_to_die = philo->table->time_to_die;
	pthread_mutex_unlock(&philo->philo_mutex);
	if (elapsed > t_to_die)
		return (true);
	return (false);
}

void	*monitor_dinner(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->philo_nbr && !simulation_finished(table))
		{
			if (philo_died(table->philos + i))
			{
				table->end_simulation = true;
				write_dead_status(table->philos, " died\n", RED);
			}
		}
	}
	return (NULL);
}
