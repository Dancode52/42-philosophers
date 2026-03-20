/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_helpers_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:13:40 by dlanehar          #+#    #+#             */
/*   Updated: 2026/03/20 08:44:42 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	odd_eat(t_philo *philos, int index)
{
	pthread_mutex_lock(&philos->sim->fork_mutex[philos->index]);
	pthread_mutex_lock(&philos->sim->fork_mutex[(philos->index + 1)
		% philos->sim->no_of_philos]);
	pthread_mutex_lock(&philos->sim->meal_mutex[index]);
	philos->meals_eaten++;
	pthread_mutex_unlock(&philos->sim->meal_mutex[index]);
	print_msg(philos, MSG_EAT);
	ft_usleep(philos->sim->time_to_eat, philos->sim);
	pthread_mutex_unlock(&philos->sim->fork_mutex[(philos->index + 1)
		% philos->sim->no_of_philos]);
	pthread_mutex_unlock(&philos->sim->fork_mutex[philos->index]);
}

void	even_eat(t_philo *philos, int index)
{
	pthread_mutex_lock(&philos->sim->fork_mutex[(philos->index + 1)
		% philos->sim->no_of_philos]);
	pthread_mutex_lock(&philos->sim->fork_mutex[philos->index]);
	pthread_mutex_lock(&philos->sim->meal_mutex[index]);
	philos->meals_eaten++;
	pthread_mutex_unlock(&philos->sim->meal_mutex[index]);
	print_msg(philos, MSG_EAT);
	ft_usleep(philos->sim->time_to_eat, philos->sim);
	pthread_mutex_unlock(&philos->sim->fork_mutex[philos->index]);
	pthread_mutex_unlock(&philos->sim->fork_mutex[(philos->index + 1)
		% philos->sim->no_of_philos]);
}

