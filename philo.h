/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:10:16 by blebas            #+#    #+#             */
/*   Updated: 2024/05/06 18:41:28 by blebas           ###   ########.fr       */
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
	int				id;
	long			meals_counter;
	bool			full;
	long			last_meal_time;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_t		thread_id;
	t_table			*table;
	pthread_mutex_t	philo_mutex;
}	t_philo;

typedef struct s_table
{
	long			philo_nbr;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nbr_limit_meals;
	long			start_simulation;
	long			threads_running_nbr;
	bool			end_simulation;
	bool			all_threads_ready;
	t_fork			*forks;
	t_philo			*philos;
	pthread_t		monitor;
	pthread_mutex_t	table_mutex;
	pthread_mutex_t	write_mutex;
}	t_table;

/* FONCTIONS */

/* utils .c */
long	ft_atol(char *nptr);
int		ft_isdigit(int c);
long	gettime(void);
void	ft_usleep(int ms);

/* init.c */
void	parse_input(t_table *table, char **argv);
void	assign_forks(t_philo *philo, t_fork *forks, int position);
void	philo_init(t_table *table);
void	data_init(t_table *table);

/* dinner.c */
void	eat(t_philo *philo);
void	*dinner_simulation(void *data);
void	dinner_start(t_table *table);

/* mtx_handle.c */
void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
bool	get_bool(pthread_mutex_t *mutex, bool *value);
void	set_long(pthread_mutex_t *mutex, long *dest, long value);
bool	get_long(pthread_mutex_t *mutex, long *value);
bool	simulation_finished(t_table *table);

/* monitor.c */
bool	philo_died(t_philo *philo);
void	*monitor_dinner(void *data);

/* synch_utils.c */
void	wait_all_threads(t_table *table);
bool	all_threads_run(pthread_mutex_t *mutex, long *threads, long philo_nbr);
void	write_dead_status(t_philo *philo, char *str, char *color);
void	write_status(t_philo *philo, char *str, char *color);

/* main.c */
int		check_digit(char **str);
int		check_args(int argc, char **argv);
int		main(int argc, char **argv);

#endif
