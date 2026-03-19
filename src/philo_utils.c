/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 09:01:47 by dlanehar          #+#    #+#             */
/*   Updated: 2026/03/19 10:02:24 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	make_threads(t_sim *sim)
{
	int	i;
	int	error;

	i = 0;
	while (i < sim->no_of_philos)
	{
		memset(&sim->philo[i], 0, sizeof(t_philo));
		sim->philo[i].id = i + 1;
		sim->philo[i].mainsim = sim;
		error = pthread_create(&sim->philo[i].philo_t, NULL, do_stuff,
				&sim->philo[i]);
		if (error != 0)
			break ;
		i++;
	}
	error = pthread_create(&sim->monitor, NULL, monitoring, sim);
	pthread_detach(sim->monitor);
	if (error != 0)
	{
		free(sim->literalfork);
		return (1);
	}
	return (0);
}

int	destroy_mutexes(t_sim *sim)
{
	int	j;
	int	error;

	j = 0;
	while (j < sim->no_of_philos)
	{
		error = pthread_mutex_destroy(&sim->literalfork[j]);
		if (error != 0)
			break ;
		j++;
	}
	error = pthread_mutex_destroy(&sim->printfprotect);
	if (error != 0)
	{
		free(sim->literalfork);
		return (1);
	}
	return (0);
}
