/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:43:42 by dlanehar          #+#    #+#             */
/*   Updated: 2026/07/29 11:02:07 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	init_mutexes(t_sim *sim)
{
	if (mutex_init_loop(sim, sim->fork_mutex) != 0)
		return (1);
	if (mutex_init_loop(sim, sim->meal_mutex) != 0)
	{
		destroy_mutexes(sim->fork_mutex, sim->no_of_philos);
		return (1);
	}
	if (pthread_mutex_init(&sim->printf_mutex, NULL) != 0)
	{
		destroy_mutexes(sim->fork_mutex, sim->no_of_philos);
		destroy_mutexes(sim->meal_mutex, sim->no_of_philos);
		return (1);
	}
	if (pthread_mutex_init(&sim->death_mutex, NULL) != 0)
	{
		destroy_mutexes(sim->fork_mutex, sim->no_of_philos);
		destroy_mutexes(sim->meal_mutex, sim->no_of_philos);
		pthread_mutex_destroy(&sim->printf_mutex);
		return (1);
	}
	return (0);
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
