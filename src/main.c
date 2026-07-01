/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 10:30:42 by dlanehar          #+#    #+#             */
/*   Updated: 2026/07/01 13:29:41 by dlanehar         ###   ########.fr       */
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

int	check_starvation(t_sim *sim, int index)
{
	int		starvation;
	size_t	current_time;

	current_time = get_time_in_ms();
	starvation = 0;
	pthread_mutex_lock(&sim->meal_mutex[index]);

	// printf("MONITOR: P%d last_meal=%zu current=%zu diff=%zu\n",
    //    index + 1,
    //    sim->philos[index].last_meal,
    //    current_time,
    //    current_time - sim->philos[index].last_meal);

	if (current_time - sim->philos[index].last_meal > (size_t)sim->time_to_die)
		starvation = 1;
	pthread_mutex_unlock(&sim->meal_mutex[index]);
	// printf("Philo %d elapsed = %zu\n",
    //    index + 1,
    //    current_time - sim->philos[index].last_meal);
	return (starvation);
}

int	all_full(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->no_of_philos)
	{
		pthread_mutex_lock(&sim->meal_mutex[i]);

		if (sim->philos[i].meals_eaten < sim->no_of_meals)
		{
			pthread_mutex_unlock(&sim->meal_mutex[i]);
			return (0);
		}

		pthread_mutex_unlock(&sim->meal_mutex[i]);
		i++;
	}
	return (1);
}

void	*monitoring(void *param)
{
	t_sim	*sim;
	int		i;

	sim = (t_sim *)param;
	while (!death_checker(sim))
	{
		i = 0;
		if (sim->no_of_meals != -1 && all_full(sim))
		{
			pthread_mutex_lock(&sim->death_mutex);
			sim->death = 1;
			pthread_mutex_unlock(&sim->death_mutex);
			return (NULL);
		}
		while (i < sim->no_of_philos)
		{
			if (check_starvation(sim, i))
			{
				pthread_mutex_lock(&sim->death_mutex);
				sim->death = 1;
				pthread_mutex_unlock(&sim->death_mutex);
				print_msg(&sim->philos[i], MSG_DIED);
				return (NULL);
			};
			i++;
			ft_usleep(5, sim);
		}
	}

	return (NULL);
}


void	*philo_routine(void *param)
{
	t_philo *philos;

	philos = (t_philo *)param;

	if (philos->sim->no_of_philos == 1)
	{
		pthread_mutex_lock(&philos->sim->fork_mutex[philos->index]);
		while(philos->sim->death != 1)
			ft_usleep(5, philos->sim);
		print_msg(philos, MSG_DIED);
		pthread_mutex_unlock(&philos->sim->fork_mutex[philos->index]);
		return (NULL);
	}
	if (philos->id % 2 == 1)
		ft_usleep(philos->sim->time_to_eat, philos->sim);
	while (!death_checker(philos->sim))
	{
		//eating

		ph_eating(philos, philos->index);
		//sleeping
		if (death_checker(philos->sim) || philos->meals_eaten >= philos->sim->no_of_meals)
			return (NULL);
		print_msg(philos, MSG_SLEEP);
		ft_usleep(philos->sim->time_to_sleep, philos->sim);
		//thinking
		if (death_checker(philos->sim))
			return (NULL);
		print_msg(philos, MSG_THINK);
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
	if (sim.no_of_philos == 1)
	{
		pthread_join(sim.philos[0].philo_t, NULL);
		error = destroy_mutexes(&sim);
		free_things(&sim);
		return (0);
	}
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
