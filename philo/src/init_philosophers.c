/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 12:52:18 by dlanehar          #+#    #+#             */
/*   Updated: 2026/07/31 15:26:23 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	check_valid_in(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == 0)
			return (1);
		i++;
	}
	return (0);
}

int	mutex_init_loop(t_sim *sim, pthread_mutex_t *ptr)
{
	int	i;
	int	error;

	i = 0;
	while (i < sim->no_of_philos)
	{
		error = pthread_mutex_init(&ptr[i], NULL);
		if (error != 0)
		{
			destroy_mutexes(ptr, i);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	create_mutex(t_sim *sim)
{
	int	error1;

	sim->fork_mutex = malloc(sim->no_of_philos * sizeof(pthread_mutex_t));
	if (!sim->fork_mutex)
		return (1);
	sim->meal_mutex = malloc(sim->no_of_philos * sizeof(pthread_mutex_t));
	if (!sim->meal_mutex)
	{
		free(sim->fork_mutex);
		return (1);
	}
	error1 = init_mutexes(sim);
	if (error1 != 0)
	{
		free(sim->fork_mutex);
		free(sim->meal_mutex);
		return (1);
	}
	return (0);
}

int	init_philosophers(t_sim *sim)
{
	int	i;

	sim->philos = malloc(sim->no_of_philos * sizeof(t_philo));
	if (!sim->philos)
		return (1);
	i = 0;
	while (i < sim->no_of_philos)
	{
		sim->philos[i].index = i;
		sim->philos[i].id = i + 1;
		sim->philos[i].last_meal = sim->progstart;
		sim->philos[i].meals_eaten = 0;
		sim->philos[i].sim = sim;
		i++;
	}
	return (0);
}

int	init_sim(char **argv, t_sim *sim)
{
	memset(sim, 0, sizeof(t_sim));
	if (check_valid_in(argv))
		return (1);
	sim->progstart = get_time_in_ms();
	sim->no_of_philos = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	if (sim->no_of_philos <= 0 || sim->time_to_die <= 0 || sim->time_to_eat < 0
		|| sim->time_to_sleep < 0)
		return (1);
	if (argv[5])
	{
		sim->no_of_meals = ft_atoi(argv[5]);
		if (sim->no_of_meals < 0)
			return (1);
	}
	else
		sim->no_of_meals = -1;
	if (init_philosophers(sim) != 0)
		return (1);
	if (create_mutex(sim) != 0)
	{
		free(sim->philos);
		return (1);
	}
	return (0);
}
