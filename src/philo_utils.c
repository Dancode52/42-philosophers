/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 09:01:47 by dlanehar          #+#    #+#             */
/*   Updated: 2026/07/24 12:15:12 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	threads_clean_exit(t_sim *sim, int i)
{
	pthread_mutex_lock(&sim->death_mutex);
	sim->death = 1;
	pthread_mutex_unlock(&sim->death_mutex);
	while (i > 0)
	{
		i--;
		pthread_join(sim->philos[i].philo_t, NULL);
	}
}

int	start_threads(t_sim *sim)
{
	int	i;
	int	error;

	i = 0;
	while (i < sim->no_of_philos)
	{
		error = pthread_create(&sim->philos[i].philo_t, NULL, philo_routine,
				&sim->philos[i]);
		if (error != 0)
		{
			threads_clean_exit(sim, i);
			return (1);
		}
		i++;
	}
	error = pthread_create(&sim->monitor, NULL, monitoring, sim);
	if (error != 0)
	{
		threads_clean_exit(sim, i);
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
		if (death_checker(sim))
			return (1);
		usleep(200);
	}
	return (0);
}
