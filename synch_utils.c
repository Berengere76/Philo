/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synch_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:29:36 by blebas            #+#    #+#             */
/*   Updated: 2024/05/06 17:12:06 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready))
		;
}

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

void	write_status(t_philo *philo, char *str, char *color)
{
	if (philo->full)
		return ;
	pthread_mutex_lock(&philo->table->write_mutex);
	printf("%s%ld%s %s%d%s%s", YELLOW, gettime()
		- philo->table->start_simulation, NC, color, philo->id, str, NC);
	pthread_mutex_unlock(&philo->table->write_mutex);
}
