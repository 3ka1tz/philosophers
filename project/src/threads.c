/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez-u <elopez-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:21:55 by elopez-u          #+#    #+#             */
/*   Updated: 2025/03/14 11:23:15 by elopez-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	destroy_mutexes(t_program *program, pthread_mutex_t *forks)
{
	int	i;

	pthread_mutex_destroy(&program->mutex_eating);
	pthread_mutex_destroy(&program->mutex_death);
	pthread_mutex_destroy(&program->mutex_log);
	i = 0;
	while (i < program->philos->number_of_philosophers)
		pthread_mutex_destroy(&forks[i++]);
}

static pthread_t	create_threads(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	observer;
	int			i;

	if (pthread_create(&observer, NULL, &monitor, program->philos) != 0)
	{
		destroy_mutexes(program, forks);
		write(2, "\033[31mError: Thread creation failed.\033[0m\n", 41);
		return ((pthread_t)0);
	}
	i = 0;
	while (i < program->philos->number_of_philosophers)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &routine, \
			&program->philos[i]) != 0)
		{
			destroy_mutexes(program, forks);
			write(2, "\033[31mError: Thread creation failed.\033[0m\n", 41);
			pthread_cancel(observer);
			return ((pthread_t)0);
		}
		i++;
	}
	return (observer);
}

static int	join_threads(t_program *program, pthread_t observer)
{
	int	i;

	if (pthread_join(observer, NULL) != 0)
	{
		destroy_mutexes(program, NULL);
		write(2, "\033[31mError: Thread join failed.\033[0m\n", 37);
		return (-1);
	}
	i = 0;
	while (i < program->philos->number_of_philosophers)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
		{
			destroy_mutexes(program, NULL);
			write(2, "\033[31mError: Thread join failed.\033[0m\n", 37);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	run_simulation(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	observer;

	observer = create_threads(program, forks);
	if (observer == (pthread_t)0)
		return (-1);
	if (join_threads(program, observer) == -1)
		return (-1);
	return (0);
}
