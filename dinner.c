/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:44:14 by blebas            #+#    #+#             */
/*   Updated: 2024/05/08 16:08:06 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_f);
	pthread_mutex_unlock(philo->right_f);
}

void	update_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->mut_last_eat_time);
	philo->last_eat_time = gettime();
	pthread_mutex_unlock(&philo->mut_last_eat_time);
}

void	update_nb_meals_had(t_philo *philo)
{
	pthread_mutex_lock(&philo->mut_nb_meals_had);
	philo->nb_meals_had++;
	pthread_mutex_unlock(&philo->mut_nb_meals_had);
}

void	sleep_for_eating(t_philo *philo)
{
	ft_usleep(get_eat_time(philo->data));
}

int	eat(t_philo *philo)
{
	if (take_forks(philo) != 0)
		return (1);
	set_philo_state(philo, EATING);
	print_msg(philo->data, philo->id, EAT, CYAN);
	update_last_meal_time(philo);
	sleep_for_eating(philo);
	update_nb_meals_had(philo);
	drop_forks(philo);
	return (0);
}
