/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 12:52:18 by dlanehar          #+#    #+#             */
/*   Updated: 2026/03/19 17:12:57 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
			free_and_destroy(sim, ptr, i);
			return (1);
		}
		i++;
	}
	return (0);
}

void	free_and_destroy(t_sim *sim, pthread_mutex_t *ptr, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		pthread_mutex_destroy(&ptr[i]);
		i++;
	}
	if (sim->fork_mutex)
		free(sim->fork_mutex);
	if (sim->philos)
		free(sim->philos);
	return ;
}

static int	create_mutex(t_sim *sim)
{
	int	j;
	int	error1;

	j = 0;
	printf("made it to create mutex\n");
	sim->fork_mutex = malloc(sim->no_of_philos * sizeof(pthread_mutex_t));
	if (!sim->fork_mutex)
		return (1);
	sim->meal_mutex = malloc(sim->no_of_philos * sizeof(pthread_mutex_t));
	if (!sim->meal_mutex)
	{
		free(sim->fork_mutex);
		free(sim->philos);
		return (1);
	}
	error1 = init_mutexes(sim);
	if (error1 != 0)
		return (1);
	return (0);
}

static int	ft_atoi(const char *str)
{
	int	i;
	int	nb;
	int	s;

	i = 0;
	nb = 0;
	s = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			s = s * -1;
		i++;
	}
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb * s);
}

int	init_sim(char **argv, t_sim *sim)
{
	memset(sim, 0, sizeof(t_sim));
	sim->progstart = get_time_in_ms();
	sim->no_of_philos = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	if (sim->no_of_philos < 0 || sim->time_to_die < 0 || sim->time_to_eat < 0
		|| sim->time_to_sleep < 0)
		return (1);
	if (argv[5])
		sim->no_of_meals = ft_atoi(argv[5]);
	else
		sim->no_of_meals = -1;
	sim->philos = malloc(sim->no_of_philos * sizeof(t_philo));
	if (!sim->philos)
		return (1);
	memset(sim->philos, 0, sim->no_of_philos * sizeof(t_philo));
	if (create_mutex(sim) != 0)
		return (1);
	return (0);
}
