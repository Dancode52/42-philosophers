/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 10:43:03 by dlanehar          #+#    #+#             */
/*   Updated: 2026/03/16 15:47:09 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_sim t_sim;

typedef struct s_philo
{
	int				id;
	pthread_t		philo_t;
	int				lastmeal;
	t_sim			*mainsim;
}	t_philo;

typedef struct s_sim
{
	int				no_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				no_of_meals;
	t_philo			philo[1024];
	int				death;
	pthread_mutex_t	*literalfork;

}	t_sim;

int	init_sim(int argc, char **argv, t_sim *sim, pthread_mutex_t *mutex);

#endif
