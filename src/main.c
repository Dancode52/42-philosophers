/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 10:30:42 by dlanehar          #+#    #+#             */
/*   Updated: 2026/03/18 18:39:44 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void *monitoring(void *param)
{
	t_sim *sim;
	int	i;

	sim = (t_sim *)param;
	i = 0;
	while(1 && sim->death == 0)
	{
		if(sim->philo[i].lastmeal > sim->time_to_die)
		{
			printf("PHILOSOPHER [%d] DIED!!\n", i + 1);
			sim->death = 1;
			return (NULL);
		}
		i = (i + 1) % sim->no_of_philos;
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
		// if (sim->death)
		// 	return (1);
		usleep(500);
	}
	return (0);
}

void *do_stuff(void *param)
{
	t_philo		*philo;
	int			pos;
	int			no_philos;
	size_t		start;

	philo = (t_philo *)param;
	start = get_time_in_ms() - philo->mainsim->basetime;
	pos = philo->id - 1;
	no_philos = philo->mainsim->no_of_philos;
	if (philo->id % 2 == 1)
		ft_usleep(philo->mainsim->time_to_eat, philo->mainsim);
	for (int f = 0; f != philo->mainsim->no_of_meals; f++){
		grab_forks(philo);
		if (philo->lastmeal > philo->mainsim->time_to_die)
		{
			pthread_mutex_lock(&philo->mainsim->printfprotect);
			printf("HERE LIES PHILOSOPHER[%d]. DIED OF STARVATION\n", philo->id);
			pthread_mutex_unlock(&philo->mainsim->printfprotect);
		}
		eat_sleep(philo, &start);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_sim	sim;
	int i;
	int j;
	int error;
	pthread_t	monitor;

	sim.basetime = get_time_in_ms();
	i = 0;
	j = 0;
	if (argc < 5 || argc > 6)
		return (1);
	if (init_sim(argv, &sim) != 0)
		return (1);
	i = 0;
	while (i < sim.no_of_philos)
	{
		sim.philo[i].id = i + 1;
		sim.philo[i].mainsim = &sim;
		pthread_create(&sim.philo[i].philo_t, NULL, do_stuff, &sim.philo[i]);
		i++;
	}
	pthread_create(&monitor, NULL, monitoring, &sim);
	i = 0;
	while (i < sim.no_of_philos)
	{
		pthread_join(sim.philo[i].philo_t, NULL);
		i++;
	}
	j = 0;
	while (j < sim.no_of_philos)
	{
		// make forks a table of mutexes
		error = pthread_mutex_destroy(&sim.literalfork[j]);
		if (error != 0)
		{
			printf("Bro, at this point throw the whole pc out...\n");
			return (1);
		}
		j++;
	}
	pthread_mutex_destroy(&sim.printfprotect);
	free(sim.literalfork);
	return (0);
}
