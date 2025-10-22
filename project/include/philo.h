/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez-u <elopez-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:05:39 by elopez-u          #+#    #+#             */
/*   Updated: 2025/02/25 09:55:59 by elopez-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define PHILO_MAX 200

typedef struct s_philo
{
	int				number_of_philosophers;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	pthread_t		thread;
	int				id;
	int				eating;
	int				times_eating;
	size_t			last_time_eating;
	size_t			start_time;
	int				*death;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*mutex_log;
	pthread_mutex_t	*mutex_death;
	pthread_mutex_t	*mutex_eating;
}					t_philo;

typedef struct s_program
{
	pthread_mutex_t	mutex_log;
	pthread_mutex_t	mutex_eating;
	pthread_mutex_t	mutex_death;
	int				death_flag;
	t_philo			*philos;
}					t_program;

// utils.c
long	ft_atol(const char *nptr);
size_t	get_current_time(void);
int		ft_usleep(size_t milliseconds);

// initialization.c
void	initialize_simulation_params(t_program *program, t_philo *philos,
			pthread_mutex_t *forks, char **argv);

// actions.c
void	*routine(void *ptr);

// monitoring.c
void	log_action(t_philo *philo, char *str);
void	*monitor(void *ptr);

// threads.c
int		run_simulation(t_program *program, pthread_mutex_t *forks);

#endif