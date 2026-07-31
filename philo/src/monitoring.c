/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 12:09:25 by dlanehar          #+#    #+#             */
/*   Updated: 2026/07/29 15:22:43 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	check_starvation(t_sim *sim, int index)
{
	int	starvation;

	starvation = 0;
	pthread_mutex_lock(&sim->meal_mutex[index]);
	if (get_time_in_ms() - sim->philos[index].last_meal
		> (size_t)sim->time_to_die)
		starvation = 1;
	pthread_mutex_unlock(&sim->meal_mutex[index]);
	return (starvation);
}

int	all_full(t_sim *sim)
{
	int	i;

	i = 0;
	if (sim->no_of_meals == -1)
		return (0);
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

static void	set_death(t_sim *sim)
{
	pthread_mutex_lock(&sim->death_mutex);
	sim->death = 1;
	pthread_mutex_unlock(&sim->death_mutex);
	return ;
}

static void	death_event(t_sim *sim, int id)
{
	size_t	time;

	pthread_mutex_lock(&sim->printf_mutex);
	time = get_time_in_ms() - sim->progstart;
	set_death(sim);
	printf("%zu %d died\n", time, id);
	pthread_mutex_unlock(&sim->printf_mutex);
	return ;
}

void	*monitoring(void *param)
{
	t_sim	*sim;
	int		i;

	sim = (t_sim *)param;
	while (!death_checker(sim))
	{
		i = 0;
		while (i < sim->no_of_philos)
		{
			if (check_starvation(sim, i))
			{
				death_event(sim, sim->philos[i].id);
				return (NULL);
			}
			i++;
		}
		if (all_full(sim))
		{
			set_death(sim);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}
