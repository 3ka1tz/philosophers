/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez-u <elopez-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:13:18 by elopez-u          #+#    #+#             */
/*   Updated: 2025/03/14 11:23:25 by elopez-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	log_action(philo, "has taken a fork");
	if (philo->number_of_philosophers == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	log_action(philo, "has taken a fork");
	philo->eating = 1;
	log_action(philo, "is eating");
	pthread_mutex_lock(philo->mutex_eating);
	philo->last_time_eating = get_current_time();
	philo->times_eating++;
	pthread_mutex_unlock(philo->mutex_eating);
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

static void	sleeping(t_philo *philo)
{
	log_action(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}

static void	thinking(t_philo *philo)
{
	log_action(philo, "is thinking");
}

static int	is_philo_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_death);
	if (*philo->death == 1)
	{
		pthread_mutex_unlock(philo->mutex_death);
		return (1);
	}
	pthread_mutex_unlock(philo->mutex_death);
	return (0);
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!is_philo_dead(philo))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (ptr);
}
