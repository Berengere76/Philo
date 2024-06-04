/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:10:16 by blebas            #+#    #+#             */
/*   Updated: 2024/05/10 09:34:56 by blebas           ###   ########.fr       */
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

# define MALLOC_ERROR 2
# define TAKE_FORKS "has taken a fork"
# define THINK "is thinking"
# define SLEEP "is sleeping"
# define EAT "is eating"
# define DIED "died"

/* STRUCTURES */

typedef enum e_philo_state
{
	EATING = 0,
	SLEEPING = 1,
	THINKING = 2,
	DEAD = 3,
	FULL = 4,
	IDLE = 5
}	t_state;

typedef struct s_philo
{
	int				id;
	int				nb_meals_had;
	struct s_data	*data;
	t_state			state;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
	pthread_mutex_t	mut_state;
	pthread_mutex_t	mut_nb_meals_had;
	pthread_mutex_t	mut_last_eat_time;
	long			last_eat_time;
}					t_philo;

typedef struct s_data
{
	int				nb_philos;
	int				nb_meals;
	int				nb_full_p;
	bool			keep_iterating;
	long			eat_time;
	long			die_time;
	long			sleep_time;
	long			start_time;
	pthread_mutex_t	mut_eat_t;
	pthread_mutex_t	mut_die_t;
	pthread_mutex_t	mut_sleep_t;
	pthread_mutex_t	mut_print;
	pthread_mutex_t	mut_nb_philos;
	pthread_mutex_t	mut_keep_iter;
	pthread_mutex_t	mut_start_time;
	pthread_t		monit_all_alive;
	pthread_t		monit_all_full;
	pthread_t		*philo_ths;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}					t_data;

/* FONCTIONS */

/* utils .c */
long	ft_atol(char *nptr);
int		ft_isdigit(int c);
long	gettime(void);
void	ft_usleep(int ms);

/* utils2.c */
int		handle_1_philo(t_philo *philo);
bool	nb_meals_option(t_data *data);
void	free_data(t_data *data);
void	print_msg(t_data *data, int id, char *msg, char *color);

/* get_set.c */
bool	get_keep_iter(t_data *data);
int		get_nb_philos(t_data *data);
t_state	get_philo_state(t_philo *philo);
int		get_nb_meals_philo_had(t_philo *philo);
long	get_start_time(t_data *data);

/* get_set2.c */
long	get_eat_time(t_data *data);
long	get_die_time(t_data *data);
long	get_sleep_time(t_data *data);
long	get_last_eat_time(t_philo *philo);

/* init.c */
int		init_forks(t_data *data);
int		init_philos(t_data *data);
int		malloc_data(t_data *data);
int		init_data(t_data *data, int argc, char **argv);

/* philo.c */
void	set_keep_iterating(t_data *data, bool set_to);
void	set_philo_state(t_philo *philo, t_state state);
int		run_threads(t_data *data);
int		join_threads(t_data *data);
int		philosophers(int argc, char **argv);

/* dinner.c */
void	drop_forks(t_philo *philo);
void	update_last_meal_time(t_philo *philo);
void	update_nb_meals_had(t_philo *philo);
void	sleep_for_eating(t_philo *philo);
int		eat(t_philo *philo);

/* dinner2.c */
void	drop_left_fork(t_philo *philo);
void	drop_right_fork(t_philo *philo);
int		take_left_fork(t_philo *philo);
int		take_right_fork(t_philo *philo);
int		take_forks(t_philo *philo);

/* routine.c */
int		ft_sleep(t_philo *philo);
int		think(t_philo *philo);
void	*routine(void *philo_p);

/* monitor.c */
bool	is_philo_full(t_data *data, t_philo *philo);
bool	philo_died(t_philo *philo);
void	*all_alive_routine(void *data);
void	*all_full_routine(void *data);

/* main.c */
int		check_digit(char **str);
int		check_args(int argc, char **argv);
int		main(int argc, char **argv);

#endif
