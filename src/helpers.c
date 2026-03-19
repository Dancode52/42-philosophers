/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:13:40 by dlanehar          #+#    #+#             */
/*   Updated: 2026/03/19 10:01:49 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	printeatmsg(t_philo *philo, size_t garbage)
{
	pthread_mutex_lock(&philo->mainsim->printfprotect);
	printf("| %zu | %d is eating.\n", garbage, philo->id);
	pthread_mutex_unlock(&philo->mainsim->printfprotect);
	ft_usleep(philo->mainsim->time_to_eat, philo->mainsim);
}

void	printsleepmsg(t_philo *philo, size_t garbage)
{
	pthread_mutex_lock(&philo->mainsim->printfprotect);
	printf("| %zu | Thread %d is sleeping!\n", garbage, philo->id);
	pthread_mutex_unlock(&philo->mainsim->printfprotect);
	ft_usleep(philo->mainsim->time_to_sleep, philo->mainsim);
}

void	eat_sleep(t_philo *philo, size_t *start)
{
	size_t	eat_time;
	size_t	garbage;

	garbage = get_time_in_ms() - philo->mainsim->basetime;
	printeatmsg(philo, garbage);
	eat_time = get_time_in_ms() - philo->mainsim->basetime;
	philo->lastmeal = eat_time - *start;
	*start = get_time_in_ms() - philo->mainsim->basetime;
	return_forks(philo);
	garbage = get_time_in_ms() - philo->mainsim->basetime;
	printsleepmsg(philo, garbage);
}
