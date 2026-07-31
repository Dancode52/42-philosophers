/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 16:43:46 by dlanehar          #+#    #+#             */
/*   Updated: 2026/07/29 11:02:07 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	free_things(t_sim *sim)
{
	if (sim->fork_mutex)
		free(sim->fork_mutex);
	if (sim->meal_mutex)
		free(sim->meal_mutex);
	if (sim->philos)
		free(sim->philos);
}

void	destroy_mutexes(pthread_mutex_t *ptr, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		pthread_mutex_destroy(&ptr[i]);
		i++;
	}
	return ;
}

void	cleanup(t_sim *sim)
{
	destroy_mutexes(sim->meal_mutex, sim->no_of_philos);
	destroy_mutexes(sim->fork_mutex, sim->no_of_philos);
	pthread_mutex_destroy(&sim->printf_mutex);
	pthread_mutex_destroy(&sim->death_mutex);
	free_things(sim);
}
