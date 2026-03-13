/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 12:52:18 by dlanehar          #+#    #+#             */
/*   Updated: 2026/03/13 17:14:24 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_atoi(const char *str)
{
	int	i;
	int	nb;
	int	s;

	i = 0;
	nb = 0;
	s = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			s = s * -1;
		i++;
	}
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb * s);
}

int	init_sim(int argc, char **argv, t_sim *sim, pthread_mutex_t *mutex)
{
	int	i;

	i = 0;
	sim->no_of_philos = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		sim->no_of_meals = ft_atoi(argv[5]);
	else
		sim->no_of_meals = -1;
	sim->death = 0;
	sim->literalfork = malloc(sim->no_of_philos * sizeof(int));
	if (!sim->literalfork)
		return (1);
	while (i < sim->no_of_philos)
		sim->literalfork[i++] = 1;
	sim->mutex = mutex;
	return (0);
}
