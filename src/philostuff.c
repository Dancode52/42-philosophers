/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philostuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 16:40:46 by dlanehar          #+#    #+#             */
/*   Updated: 2026/03/19 14:54:53 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static	void	odd_forks(t_philo *philo, int nphil, int pos)
{
	size_t	garbage;

	pthread_mutex_lock(&philo->sim->fork_mutex[pos]);
	garbage = get_time_in_ms() - philo->sim->progstart;
	pthread_mutex_lock(&philo->sim->printf_mutex);
	printf("| %zu | %d has taken a fork.\n", garbage, philo->id);
	pthread_mutex_unlock(&philo->sim->printf_mutex);
	pthread_mutex_lock(&philo->sim->fork_mutex[(pos + 1) % nphil]);
	garbage = get_time_in_ms() - philo->sim->progstart;
	pthread_mutex_lock(&philo->sim->printf_mutex);
	printf("| %zu | %d has taken a fork.\n", garbage, philo->id);
	pthread_mutex_unlock(&philo->sim->printf_mutex);
}

static	void	even_forks(t_philo *philo, int nphil, int pos)
{
	size_t	garbage;

	pthread_mutex_lock(&philo->sim->fork_mutex[(pos + 1) % nphil]);
	garbage = get_time_in_ms() - philo->sim->progstart;
	pthread_mutex_lock(&philo->sim->printf_mutex);
	printf("| %zu | %d has taken a fork.\n", garbage, philo->id);
	pthread_mutex_unlock(&philo->sim->printf_mutex);
	pthread_mutex_lock(&philo->sim->fork_mutex[pos]);
	garbage = get_time_in_ms() - philo->sim->progstart;
	pthread_mutex_lock(&philo->sim->printf_mutex);
	printf("| %zu | %d has taken a fork.\n", garbage, philo->id);
	pthread_mutex_unlock(&philo->sim->printf_mutex);
}

void	grab_forks(t_philo *philo)
{
	int		no_philos;
	int		pos;

	no_philos = philo->sim->no_of_philos;
	pos = philo->id - 1;
	if (philo->id % 2 == 1)
		odd_forks(philo, no_philos, pos);
	else
		even_forks(philo, no_philos, pos);
}

void	return_forks(t_philo *philo)
{
	int			pos;
	int			no_philos;

	pos = philo->id - 1;
	no_philos = philo->sim->no_of_philos;
	if (philo->id % 2 == 1)
	{
		pthread_mutex_unlock(&philo->sim->fork_mutex[(pos + 1)
			% no_philos]);
		pthread_mutex_unlock(&philo->sim->fork_mutex[pos]);
	}
	else
	{
		pthread_mutex_unlock(&philo->sim->fork_mutex[pos]);
		pthread_mutex_unlock(&philo->sim->fork_mutex[(pos + 1)
			% no_philos]);
	}
}
