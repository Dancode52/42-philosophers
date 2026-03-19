/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 10:30:42 by dlanehar          #+#    #+#             */
/*   Updated: 2026/03/19 18:38:48 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_things(t_sim *sim)
{
	if (sim->fork_mutex)
		free(sim->fork_mutex);
	if (sim->meal_mutex)
		free(sim->meal_mutex);
	if (sim->philos)
		free(sim->philos);
}

void	*monitoring(void *param)
{
	t_sim	*sim;

	sim = (t_sim *)param;

	// if (/*we find out someone died*/)
	// {
	// 	pthread_mutex_lock(&sim->death_mutex);
	// 	sim->death = 1;
	// 	pthread_mutex_unlock(&sim->death_mutex);
	// }

	return (NULL);
}

void	*philo_routine(void *param)
{
	t_philo *philos;

	philos = (t_philo *)param;

	if (philos->id % 2 == 1)
		ft_usleep(philos->sim->time_to_eat, philos->sim);
	while (!death_checker(philos->sim) && !meal_checker(philos->sim, philos->index))
	{
		//eating
		ph_eating(philos, philos->index);
		ft_usleep(philos->sim->time_to_sleep, philos->sim);
		//sleeping
		//thinking
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_sim	sim;
	int		i;
	int		error;

	sim.progstart = get_time_in_ms();
	i = 0;
	if (argc < 5 || argc > 6)
		return (1);
	error = init_sim(argv, &sim);
	if (error != 0)
		return (1);
	error = make_threads(&sim);
	if (error == 1)
		return (1);
	while (i < sim.no_of_philos)
	{
		pthread_join(sim.philos[i].philo_t, NULL);
		i++;
	}
	error = destroy_mutexes(&sim);
	if (error == 1)
		return (1);
	free_things(&sim);
	return (0);
}
