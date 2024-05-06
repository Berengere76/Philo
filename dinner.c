/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:44:14 by blebas            #+#    #+#             */
/*   Updated: 2024/05/06 18:35:14 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	write_status(philo, " has taken a fork\n", GREEN);
	pthread_mutex_lock(&philo->second_fork->fork);
	write_status(philo, " has taken a fork\n", GREEN);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime());
	pthread_mutex_lock(&philo->philo_mutex);
	philo->meals_counter++;
	pthread_mutex_unlock(&philo->philo_mutex);
	write_status(philo, " is eating\n", CYAN);
	ft_usleep(philo->table->time_to_eat);
	if (philo->table->nbr_limit_meals > 0
		&& philo->meals_counter == philo->table->nbr_limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime());
	pthread_mutex_lock(&philo->table->table_mutex);
	philo->table->threads_running_nbr++;
	pthread_mutex_unlock(&philo->table->table_mutex);
	while (!simulation_finished(philo->table))
	{
		if (philo->full)
			break ;
		eat(philo);
		if (simulation_finished(philo->table))
			break ;
		write_status(philo, " is sleeping\n", BLUE);
		ft_usleep(philo->table->time_to_sleep);
		write_status(philo, " is thinking\n", PURPLE);
	}
	return (NULL);
}

void	lone_philo(t_philo	*philo)
{
	printf("%s%li 1 has taken a fork%s\n", GREEN,
		gettime() - philo->table->start_simulation, NC);
	ft_usleep(philo->table->time_to_die);
	printf("%s%li 1 died%s\n", RED, philo->table->time_to_die, NC);
}

void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	table->start_simulation = gettime();
	if (table->philo_nbr == 0)
		return ;
	if (table->nbr_limit_meals == 0)
		return ;
	if (table->philo_nbr == 1)
	{
		lone_philo(table->philos);
		return ;
	}
	while (++i < table->philo_nbr)
		pthread_create(&table->philos[i].thread_id, NULL, dinner_simulation,
			&table->philos[i]);
	pthread_create(&table->monitor, NULL, monitor_dinner, table);
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	i = -1;
	while (++i < table->philo_nbr)
		pthread_join(table->philos[i].thread_id, NULL);
	set_bool(&table->table_mutex, &table->end_simulation, true);
	pthread_join(table->monitor, NULL);
}
