/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 10:30:42 by dlanehar          #+#    #+#             */
/*   Updated: 2026/03/13 15:58:35 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	do_stuff(void *param);

int	main(int argc, char **argv)
{
	t_sim	sim;
	pthread_t	philo_t[1024];
	int i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (1);
	init_sim(argc, argv, &sim);
	while (i < sim.no_of_philos)
	{
		sim.philo[i].id = i + 1;
		pthread_create(&sim.philo[i].philo_t, NULL, do_stuff, &sim);
		i++;
	}
	
}
