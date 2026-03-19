/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philostuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 16:40:46 by dlanehar          #+#    #+#             */
/*   Updated: 2026/03/19 10:01:18 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static	void	odd_forks(t_philo *philo, int nphil, int pos)
{
	size_t	garbage;

	pthread_mutex_lock(&philo->mainsim->literalfork[pos]);
	garbage = get_time_in_ms() - philo->mainsim->basetime;
	pthread_mutex_lock(&philo->mainsim->printfprotect);
	printf("| %zu | %d has taken a fork.\n", garbage, philo->id);
	pthread_mutex_unlock(&philo->mainsim->printfprotect);
	pthread_mutex_lock(&philo->mainsim->literalfork[(pos + 1) % nphil]);
	garbage = get_time_in_ms() - philo->mainsim->basetime;
	pthread_mutex_lock(&philo->mainsim->printfprotect);
	printf("| %zu | %d has taken a fork.\n", garbage, philo->id);
	pthread_mutex_unlock(&philo->mainsim->printfprotect);
}

static	void	even_forks(t_philo *philo, int nphil, int pos)
{
	size_t	garbage;

	pthread_mutex_lock(&philo->mainsim->literalfork[(pos + 1) % nphil]);
	garbage = get_time_in_ms() - philo->mainsim->basetime;
	pthread_mutex_lock(&philo->mainsim->printfprotect);
	printf("| %zu | %d has taken a fork.\n", garbage, philo->id);
	pthread_mutex_unlock(&philo->mainsim->printfprotect);
	pthread_mutex_lock(&philo->mainsim->literalfork[pos]);
	garbage = get_time_in_ms() - philo->mainsim->basetime;
	pthread_mutex_lock(&philo->mainsim->printfprotect);
	printf("| %zu | %d has taken a fork.\n", garbage, philo->id);
	pthread_mutex_unlock(&philo->mainsim->printfprotect);
}

void	grab_forks(t_philo *philo)
{
	int		no_philos;
	int		pos;

	no_philos = philo->mainsim->no_of_philos;
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
	no_philos = philo->mainsim->no_of_philos;
	if (philo->id % 2 == 1)
	{
		pthread_mutex_unlock(&philo->mainsim->literalfork[(pos + 1)
			% no_philos]);
		pthread_mutex_unlock(&philo->mainsim->literalfork[pos]);
	}
	else
	{
		pthread_mutex_unlock(&philo->mainsim->literalfork[pos]);
		pthread_mutex_unlock(&philo->mainsim->literalfork[(pos + 1)
			% no_philos]);
	}
}
