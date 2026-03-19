/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 09:01:47 by dlanehar          #+#    #+#             */
/*   Updated: 2026/03/19 17:02:39 by dlanehar         ###   ########.fr       */
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
		sim->philos[i].index = i;
		sim->philos[i].id = i + 1;
		sim->philos[i].sim = sim;
		error = pthread_create(&sim->philos[i].philo_t, NULL, philo_routine,
				&sim->philos[i]);
		if (error != 0)
			break ;
		i++;
	}
	error = pthread_create(&sim->monitor, NULL, monitoring, sim);
	if (error != 0)
	{
		free_and_destroy(sim, sim->fork_mutex, sim->no_of_philos);
		free_and_destroy(sim, sim->meal_mutex, sim->no_of_philos);
		return (1);
	}
	pthread_detach(sim->monitor);
	return (0);
}

int	destroy_mutexes(t_sim *sim)
{
	int	j;
	int	error;

	j = 0;
	while (j < sim->no_of_philos)
	{
		error = pthread_mutex_destroy(&sim->fork_mutex[j]);
		if (error != 0)
			break ;
		j++;
	}
	error = pthread_mutex_destroy(&sim->printf_mutex);
	if (error != 0)
	{
		free(sim->fork_mutex);
		return (1);
	}
	return (0);
}

size_t	get_time_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t ms, t_sim *sim)
{
	size_t	start;

	(void)sim;
	start = get_time_in_ms();
	while ((get_time_in_ms() - start) < ms)
	{
		if (sim->death)
			return (1);
		usleep(500);
	}
	return (0);
}
