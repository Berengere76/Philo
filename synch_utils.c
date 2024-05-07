/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synch_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:29:36 by blebas            #+#    #+#             */
/*   Updated: 2024/05/07 12:24:30 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_dead_status(t_philo *philo, char *str, char *color)
{
	pthread_mutex_lock(&philo->table->write_mutex);
	printf("%s%ld%s %s%d%s%s", YELLOW, gettime()
		- philo->table->start_simulation, NC, color, philo->id, str, NC);
	pthread_mutex_unlock(&philo->table->write_mutex);
}

void	write_status(t_philo *philo, char *str, char *color)
{
	pthread_mutex_lock(&philo->table->write_mutex);
	if (philo->full)
	{
		pthread_mutex_unlock(&philo->table->write_mutex);
		return ;
	}
	if (!simulation_finished(philo->table))
	{
		printf("%s%ld%s %s%d%s%s", YELLOW, gettime()
			- philo->table->start_simulation, NC, color, philo->id, str, NC);
		pthread_mutex_unlock(&philo->table->write_mutex);
	}
	else
		pthread_mutex_unlock(&philo->table->write_mutex);
}
