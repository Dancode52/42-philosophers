/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 10:30:42 by dlanehar          #+#    #+#             */
/*   Updated: 2026/03/19 10:00:36 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitoring(void *param)
{
	t_sim	*sim;
	size_t	time;
	int		i;

	sim = (t_sim *)param;
	i = 0;
	while (sim->death == 0)
	{
		i = 0;
		while (i < sim->no_of_philos)
		{
			if (sim->philo[i].lastmeal > sim->time_to_die)
			{
				ft_usleep(5, sim);
				time = get_time_in_ms() - sim->basetime;
				printf("| %zu |Philospher[%d] thought himself"
					" to death...\n", time, i + 1);
				sim->death = 1;
				return (NULL);
			}
			i++;
			ft_usleep(5, sim);
		}
	}
	return (NULL);
}

size_t	get_time_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t ms, t_sim *sim)
{
	size_t	start;

	(void)sim;
	start = get_time_in_ms();
	while ((get_time_in_ms() - start) < ms)
	{
		if (sim->death)
			return (1);
		usleep(500);
	}
	return (0);
}

void	*do_stuff(void *param)
{
	t_philo		*philo;
	size_t		start;
	int			i;

	i = 0;
	philo = (t_philo *)param;
	start = get_time_in_ms() - philo->mainsim->basetime;
	if (philo->id % 2 == 1)
		ft_usleep(philo->mainsim->time_to_eat, philo->mainsim);
	while (i != philo->mainsim->no_of_meals && philo->mainsim->death != 1)
	{
		grab_forks(philo);
		if (philo->lastmeal > philo->mainsim->time_to_die)
		{
			pthread_mutex_lock(&philo->mainsim->printfprotect);
			printf("HERE LIES PHILOSOPHER[%d]. DIED OF STARVATION\n",
				philo->id);
			pthread_mutex_unlock(&philo->mainsim->printfprotect);
		}
		eat_sleep(philo, &start);
		i++;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_sim	sim;
	int		i;
	int		error;

	sim.basetime = get_time_in_ms();
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
		pthread_join(sim.philo[i].philo_t, NULL);
		i++;
	}
	error = destroy_mutexes(&sim);
	if (error == 1)
		return (1);
	free(sim.literalfork);
	return (0);
}
