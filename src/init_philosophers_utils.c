/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:43:42 by dlanehar          #+#    #+#             */
/*   Updated: 2026/07/02 12:51:35 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_mutexes(t_sim *sim)
{
	int	error1;
	int	error2;

	error1 = mutex_init_loop(sim, sim->fork_mutex);
	if (error1 != 0)
		return (1);
	error2 = mutex_init_loop(sim, sim->meal_mutex);
	if (error2 != 0)
	{
		free_and_destroy(sim, sim->fork_mutex, sim->no_of_philos);
		return (1);
	}
	if (pthread_mutex_init(&sim->printf_mutex, NULL) != 0)
	{
		free_and_destroy(sim, sim->fork_mutex, sim->no_of_philos);
		free_and_destroy(sim, sim->meal_mutex, sim->no_of_philos);
		return (1);
	}
	if (pthread_mutex_init(&sim->death_mutex, NULL) != 0)
	{
		free_and_destroy(sim, sim->fork_mutex, sim->no_of_philos);
		free_and_destroy(sim, sim->meal_mutex, sim->no_of_philos);
		return (1);
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

int	ft_atoi(const char *str)
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
