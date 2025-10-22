/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez-u <elopez-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:10:38 by elopez-u          #+#    #+#             */
/*   Updated: 2025/02/24 12:42:36 by elopez-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	is_numeric_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	are_arguments_valid(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (write(2, "\033[31mError: Invalid "
				"number of arguments.\033[0m\n", 46), 0);
	if (!is_numeric_string(argv[1]) || ft_atol(argv[1]) <= 0)
		return (write(2, "\033[31mError: Invalid "
				"number of philosophers.\033[0m\n", 49), 0);
	if (ft_atol(argv[1]) > PHILO_MAX)
		return (printf("\033[31mError: The maximum number of philosophers "
				"is set to %d.\033[0m\n", PHILO_MAX), 0);
	if (!is_numeric_string(argv[2]) || ft_atol(argv[2]) <= 0)
		return (write(2, "\033[31mError: Invalid "
				"time to die.\033[0m\n", 38), 0);
	if (!is_numeric_string(argv[3]) || ft_atol(argv[3]) <= 0)
		return (write(2, "\033[31mError: Invalid "
				"time to eat.\033[0m\n", 38), 0);
	if (!is_numeric_string(argv[4]) || ft_atol(argv[4]) <= 0)
		return (write(2, "\033[31mError: Invalid "
				"time to sleep.\033[0m\n", 40), 0);
	if (argv[5] && (!is_numeric_string(argv[5]) || ft_atol(argv[5]) <= 0))
		return (write(2, "\033[31mError: Invalid "
				"number of times each philosopher must eat.\033[0m\n", 68), 0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_program		program;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (!are_arguments_valid(argc, argv))
		return (1);
	initialize_simulation_params(&program, philos, forks, argv);
	run_simulation(&program, forks);
	return (0);
}
