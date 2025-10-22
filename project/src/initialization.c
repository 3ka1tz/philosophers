/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez-u <elopez-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 10:54:45 by elopez-u          #+#    #+#             */
/*   Updated: 2025/02/25 09:54:41 by elopez-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	initialize_program(t_program *program, t_philo *philos)
{
	program->death_flag = 0;
	program->philos = philos;
	pthread_mutex_init(&program->mutex_log, NULL);
	pthread_mutex_init(&program->mutex_death, NULL);
	pthread_mutex_init(&program->mutex_eating, NULL);
}

static void	initialize_forks(pthread_mutex_t *forks, int number_of_philosophers)
{
	int	i;

	i = 0;
	while (i < number_of_philosophers)
		pthread_mutex_init(&forks[i++], NULL);
}

static void	initialize_philo_input(t_philo *philo, char **argv)
{
	philo->number_of_philosophers = ft_atol(argv[1]);
	philo->time_to_die = ft_atol(argv[2]);
	philo->time_to_eat = ft_atol(argv[3]);
	philo->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		philo->number_of_times_each_philosopher_must_eat = ft_atol(argv[5]);
	else
		philo->number_of_times_each_philosopher_must_eat = -1;
}

static void	initialize_philosophers(t_program *program, t_philo *philos,
									pthread_mutex_t *forks, char **argv)
{
	int	i;
	int	number_of_philosophers;

	i = 0;
	number_of_philosophers = ft_atol(argv[1]);
	while (i < number_of_philosophers)
	{
		initialize_philo_input(&philos[i], argv);
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].times_eating = 0;
		philos[i].start_time = get_current_time();
		philos[i].last_time_eating = get_current_time();
		philos[i].mutex_log = &program->mutex_log;
		philos[i].mutex_death = &program->mutex_death;
		philos[i].mutex_eating = &program->mutex_eating;
		philos[i].death = &program->death_flag;
		philos[i].l_fork = &forks[i];
		if (i == 0)
			philos[i].r_fork = &forks[philos[i].number_of_philosophers - 1];
		else
			philos[i].r_fork = &forks[i - 1];
		i++;
	}
}

void	initialize_simulation_params(t_program *program, t_philo *philos,
								pthread_mutex_t *forks, char **argv)
{
	initialize_program(program, philos);
	initialize_forks(forks, ft_atol(argv[1]));
	initialize_philosophers(program, philos, forks, argv);
}
