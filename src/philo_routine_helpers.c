/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:13:40 by dlanehar          #+#    #+#             */
/*   Updated: 2026/03/20 08:46:15 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_msg(t_philo *philos, t_msg_type type)
{
    size_t time;

	time = get_time_in_ms() - philos->sim->progstart;
    pthread_mutex_lock(&philos->sim->printf_mutex);
    if (type == MSG_FORK)
        printf("%zu %d has taken a fork\n", time, philos->id);
    else if (type == MSG_EAT)
        printf("%zu %d is eating\n", time, philos->id);
    else if (type == MSG_SLEEP)
        printf("%zu %d is sleeping\n", time, philos->id);
    else if (type == MSG_THINK)
        printf("%zu %d is thinking\n", time, philos->id);
    else if (type == MSG_DIED)
        printf("%zu %d died\n", time, philos->id);
    pthread_mutex_unlock(&philos->sim->printf_mutex);
}

int	death_checker(t_sim *sim)
{
	int	dead;

	pthread_mutex_lock(&sim->death_mutex);
	dead = sim->death;
	pthread_mutex_unlock(&sim->death_mutex);
	return (dead);
}

int	meal_checker(t_sim *sim, int index)
{
	int	full;

	full = 0;
	pthread_mutex_lock(&sim->meal_mutex[index]);
	if (sim->philos[index].meals_eaten == sim->no_of_meals)
		full = 1;
	pthread_mutex_unlock(&sim->meal_mutex[index]);
	return (full);
}
int	ph_eating(t_philo *philos, int index)
{
	pthread_mutex_lock(philos->sim->meal_mutex);
	philos->last_meal = get_time_in_ms();
	pthread_mutex_lock(philos->sim->meal_mutex);
	if (philos->id % 2 == 1)
	{
		odd_eat(philos, index);
	}
	else
	{
		even_eat(philos, index);
	}
	return (0);
}
