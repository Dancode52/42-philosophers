/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 10:30:42 by dlanehar          #+#    #+#             */
/*   Updated: 2026/03/17 11:25:52 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_and_destroy(t_sim *sim, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		pthread_mutex_destroy(&sim->literalfork[i]);
		i++;
	}
	free(sim->literalfork);
	return ;
}

size_t	get_time_in_ms(void)
{
	int		stms;
	int		ustms;
	struct timeval	time;

	gettimeofday(&time, NULL);
	stms = time.tv_sec * 1000;
	ustms = time.tv_usec / 1000;
	return (stms + ustms);
}

void *do_stuff(void *param)
{
	t_philo	*philo;
	int		pos;
	int		no_philos;
	int		lastmeal;

	for (int f = 0; f < 10; f++){
		philo = (t_philo *)param;
		pos = philo->id - 1;
		no_philos = philo->mainsim->no_of_philos;
		// try and take fork to eat
		pthread_mutex_lock(&philo->mainsim->literalfork[pos]);
		pthread_mutex_lock(&philo->mainsim->literalfork[(pos + 1) % no_philos]);
		// eat
		usleep(philo->mainsim->time_to_eat * 1000);
		printf("Thread %d is eating!\nI have eaten %d meals!\n\n", philo->id, f+1);
		// give back forks
		pthread_mutex_unlock(&philo->mainsim->literalfork[pos]);
		pthread_mutex_unlock(&philo->mainsim->literalfork[(pos + 1) % no_philos]);
		// sleep
		printf("Thread %d is sleeping! Good night!\n\n", philo->id);
		usleep(philo->mainsim->time_to_sleep);
	}
	return (NULL);
}

// void	*do_stuff(void *param)
// {
// 	t_philo	*philosopher;
// 	philosopher = (t_philo *)param;
// 	int		id;

// 	id = philosopher->id - 1;

// 	int		n = philosopher->mainsim->no_of_philos;
// 	int		rfork = (((id + 1) % n) + n) % n;
// 	int		lfork = (((id - 1) % n) + n) % n;

// 	printf("id = %d\n", id);
// 	pthread_mutex_lock(philosopher->mainsim->mutex1);
// 	philosopher->mainsim->literalfork[rfork] = 0;
// 	philosopher->mainsim->literalfork[lfork] = 0;
// 	printf("id - 1 mod n: %d id + 1 mod n: %d\n", lfork, rfork);
// 	printf("Thread: %d l fork: %d r fork: %d\n", id, philosopher->mainsim->literalfork[lfork], philosopher->mainsim->literalfork[rfork]);
// 	pthread_mutex_unlock(philosopher->mainsim->mutex1);
// 	// stop traking last meal here. he is eating. saves timer and should be checked.
// 	//usleep(philosopher->mainsim->time_to_eat);
// 	usleep(50);
// 	// get "last meal" time start here. This is the point just after eating.
// 	pthread_mutex_lock(philosopher->mainsim->mutex2);
// 	philosopher->mainsim->literalfork[rfork] = 1;
// 	philosopher->mainsim->literalfork[lfork] = 1;
// 	printf("id - 1 mod n: %d id + 1 mod n: %d\n", lfork, rfork);
// 	printf("Thread: %d l fork: %d r fork: %d\n", id, philosopher->mainsim->literalfork[lfork], philosopher->mainsim->literalfork[rfork]);
// 	pthread_mutex_unlock(philosopher->mainsim->mutex2);
// 	// set sleep time here.
// 	usleep(philosopher->mainsim->time_to_sleep);
// 	return (NULL);
// }

int	main(int argc, char **argv)
{
	t_sim	sim;
	pthread_mutex_t mutex1;
	pthread_mutex_t mutex2;
	int i;
	int j;
	int error;

	i = 0;
	j = 0;
	if (argc < 5 || argc > 6)
		return (1);
	pthread_mutex_init(&mutex1, NULL);
	pthread_mutex_init(&mutex2, NULL);
	if (init_sim(argc, argv, &sim, &mutex1))
		return (1);
	sim.literalfork = malloc(sim.no_of_philos * sizeof(pthread_mutex_t));
	while (j < sim.no_of_philos)
	{
		// make forks a table of mutexes
		error = pthread_mutex_init(&sim.literalfork[j], NULL);
		if (error != 0)
		{
			free_and_destroy(&sim, j);
			return (1);
		}
		j++;
		printf("no of forks = %d\n", j);
	}
	i = 0;
	while (i < sim.no_of_philos)
	{
		sim.philo[i].id = i + 1;
		sim.philo[i].mainsim = &sim;
		pthread_create(&sim.philo[i].philo_t, NULL, do_stuff, &sim.philo[i]);
		i++;
	}
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
	free(sim.literalfork);
	return (0);
}
