/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:10:16 by blebas            #+#    #+#             */
/*   Updated: 2024/04/30 17:03:50 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* LIBRARY */

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>

/* COLORS */

# define NC		"\e[0m"
# define YELLOW	"\e[1;33m"
# define RED	"\e[1;31m"
# define GREEN	"\e[1;32m"
# define PURPLE	"\e[1;35m"
# define CYAN	"\e[1;36m"
# define BLUE	"\e[1;34m"

/* STRUCTURES */

typedef struct s_table	t_table;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}	t_fork;

typedef struct s_philo
{
	int			id;
	long		meals_counter;
	bool		full;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_table		*table;
}	t_philo;

typedef struct s_table
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nbr_limit_meals;
	long		start_simulation;
	bool		end_simulation;
	t_fork		*forks;
	t_philo		*philos;
	pthread_mutex_t	table_mutex;
}	t_table;

/* FONCTIONS */

/* utils .c */
long	ft_atol(char *nptr);
int		ft_isdigit(int c);

/* init.c */
void	parse_input(t_table *table, char **argv);
void	assign_forks(t_philo *philo, t_fork *forks, int position);
void	philo_init(t_table *table);
void	data_init(t_table *table);

/* dinner.c */
void	*dinner_simulation(void *data);
void	dinner_start(t_table *table);

/* main.c */
int		check_digit(char **str);
int		check_input(int argc, char **argv);
int		check_args(int argc, char **argv);
int		main(int argc, char **argv);

#endif
