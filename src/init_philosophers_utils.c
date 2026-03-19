/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:43:42 by dlanehar          #+#    #+#             */
/*   Updated: 2026/03/19 17:06:40 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_mutexes(t_sim *sim)
{
	int	error1;
	int	error2;

	printf("made it to init mutexes\n");
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
	return (0);
}
