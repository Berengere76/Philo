/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synch_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:29:36 by blebas            #+#    #+#             */
/*   Updated: 2024/05/06 19:38:54 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	all_threads_run(pthread_mutex_t *mutex, long *threads, long philo_nbr)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(mutex);
	if (*threads == philo_nbr)
		ret = true;
	pthread_mutex_unlock(mutex);
	return (ret);
}

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
