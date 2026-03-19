/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:13:40 by dlanehar          #+#    #+#             */
/*   Updated: 2026/03/19 18:39:11 by dlanehar         ###   ########.fr       */
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
	if (philos->id % 2 == 1)
	{
		pthread_mutex_lock(&philos->sim->fork_mutex[philos->index]);
		pthread_mutex_lock(&philos->sim->fork_mutex[(philos->index + 1) % philos->sim->no_of_philos]);
		pthread_mutex_lock(&philos->sim->meal_mutex[index]);
		philos->meals_eaten++;
		pthread_mutex_unlock(&philos->sim->meal_mutex[index]);
		print_msg(philos, MSG_EAT);
		ft_usleep(philos->sim->time_to_eat, philos->sim);
		pthread_mutex_unlock(&philos->sim->fork_mutex[(philos->index + 1) % philos->sim->no_of_philos]);
		pthread_mutex_unlock(&philos->sim->fork_mutex[philos->index]);
	}
	else
	{
		pthread_mutex_lock(&philos->sim->fork_mutex[(philos->index + 1) % philos->sim->no_of_philos]);
		pthread_mutex_lock(&philos->sim->fork_mutex[philos->index]);
		pthread_mutex_lock(&philos->sim->meal_mutex[index]);
		philos->meals_eaten++;
		pthread_mutex_unlock(&philos->sim->meal_mutex[index]);
		print_msg(philos, MSG_EAT);
		ft_usleep(philos->sim->time_to_eat, philos->sim);
		pthread_mutex_unlock(&philos->sim->fork_mutex[philos->index]);
		pthread_mutex_unlock(&philos->sim->fork_mutex[(philos->index + 1) % philos->sim->no_of_philos]);
	}
	return (0);
}
