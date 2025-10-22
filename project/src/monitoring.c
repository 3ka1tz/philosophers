/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez-u <elopez-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:57:16 by elopez-u          #+#    #+#             */
/*   Updated: 2025/02/25 09:54:43 by elopez-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	log_action(t_philo *philo, char *str)
{
	size_t	time;

	pthread_mutex_lock(philo->mutex_log);
	time = get_current_time() - philo->start_time;
	if (*philo->death != 1)
		printf("\033[34m%zu	%d	%s\033[0m\n", time, philo->id, str);
	pthread_mutex_unlock(philo->mutex_log);
}

static int	starved_to_death(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_eating);
	if (get_current_time() - philo->last_time_eating >= philo->time_to_die
		&& philo->eating == 0)
		return (pthread_mutex_unlock(philo->mutex_eating), 1);
	pthread_mutex_unlock(philo->mutex_eating);
	return (0);
}

static int	log_death(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->number_of_philosophers)
	{
		if (starved_to_death(&philos[i]))
		{
			log_action(&philos[i], "\033[31mdied\033[0m");
			pthread_mutex_lock(philos->mutex_death);
			*philos->death = 1;
			pthread_mutex_unlock(philos->mutex_death);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	all_philos_ate_enough(t_philo *philos)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (philos->number_of_times_each_philosopher_must_eat == -1)
		return (0);
	while (i < philos->number_of_philosophers)
	{
		pthread_mutex_lock(philos[i].mutex_eating);
		if (philos[i].times_eating
			>= philos[i].number_of_times_each_philosopher_must_eat)
			finished_eating++;
		pthread_mutex_unlock(philos[i].mutex_eating);
		i++;
	}
	if (finished_eating == philos->number_of_philosophers)
	{
		pthread_mutex_lock(philos->mutex_death);
		*philos->death = 1;
		pthread_mutex_unlock(philos->mutex_death);
		return (1);
	}
	return (0);
}

void	*monitor(void *ptr)
{
	t_philo	*philos;

	philos = (t_philo *)ptr;
	while (1)
		if (log_death(philos)
			|| all_philos_ate_enough(philos))
			break ;
	return (ptr);
}
