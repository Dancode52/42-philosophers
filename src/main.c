/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 10:30:42 by dlanehar          #+#    #+#             */
/*   Updated: 2026/07/24 14:57:31 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	single_philo_func(t_philo *philos)
{
	pthread_mutex_lock(&philos->sim->fork_mutex[philos->index]);
	print_msg(philos, MSG_FORK);
	while (!death_checker(philos->sim))
		ft_usleep(5, philos->sim);
	pthread_mutex_unlock(&philos->sim->fork_mutex[philos->index]);
	return ;
}

void	*philo_routine(void *param)
{
	t_philo	*philos;

	philos = (t_philo *)param;
	if (philos->sim->no_of_philos == 1)
	{
		single_philo_func(philos);
		return (NULL);
	}
	if (philos->id % 2 == 1)
		ft_usleep(philos->sim->time_to_eat, philos->sim);
	while (!death_checker(philos->sim))
	{
		ph_eating(philos, philos->index);
		if (death_checker(philos->sim))
			return (NULL);
		print_msg(philos, MSG_SLEEP);
		ft_usleep(philos->sim->time_to_sleep, philos->sim);
		if (death_checker(philos->sim))
			return (NULL);
		print_msg(philos, MSG_THINK);
	}
	return (NULL);
}

int	set_up_sim(int argc, char **argv, t_sim *sim)
{
	int	error;

	if (argc < 5 || argc > 6)
		return (1);
	error = init_sim(argv, sim);
	if (error == 1)
		return (1);
	return (0);
}

int	run_sim(t_sim *sim)
{
	int	error;
	int	i;

	i = 0;
	error = start_threads(sim);
	if (error == 1)
		return (1);
	if (sim->no_of_philos == 1)
	{
		pthread_join(sim->philos[0].philo_t, NULL);
		pthread_join(sim->monitor, NULL);
		return (0);
	}
	i = 0;
	while (i < sim->no_of_philos)
	{
		pthread_join(sim->philos[i].philo_t, NULL);
		i++;
	}
	pthread_join(sim->monitor, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_sim	sim;
	int		sim_val;

	if (set_up_sim(argc, argv, &sim) != 0)
		return (1);
	sim_val = run_sim(&sim);
	cleanup(&sim);
	return (sim_val);
}
