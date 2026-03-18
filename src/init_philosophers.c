/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 12:52:18 by dlanehar          #+#    #+#             */
/*   Updated: 2026/03/18 16:59:05 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	free_and_destroy(t_sim *sim, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		pthread_mutex_destroy(&sim->literalfork[i]);
		i++;
	}
	free(sim->literalfork);
	return ;
}

static int	init_mutex(t_sim *sim)
{
	int	j;
	int	error;

	j = 0;
	sim->literalfork = malloc(sim->no_of_philos * sizeof(pthread_mutex_t));
	while (j < sim->no_of_philos)
	{
		// make forks a table of mutexes
		error = pthread_mutex_init(&sim->literalfork[j], NULL);
		if (error != 0)
		{
			free_and_destroy(sim, j);
			return (1);
		}
		j++;
		printf("no of forks = %d\n", j);
	}
	if (pthread_mutex_init(&sim->printfprotect, NULL) != 0)
	{
		free_and_destroy(sim, j);
		return (1);
	}
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
	int	i;

	i = 0;
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
	sim->death = 0;
	if (init_mutex(sim) != 0)
		return (1);
	return (0);
}
