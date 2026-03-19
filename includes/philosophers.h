/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 10:43:03 by dlanehar          #+#    #+#             */
/*   Updated: 2026/03/19 10:31:03 by dlanehar         ###   ########.fr       */
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

typedef	struct	s_sim	t_sim;

typedef	struct	s_philo
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
	pthread_mutex_t	printfprotect;
	size_t			basetime;
	pthread_t		monitor;

}	t_sim;

int		init_sim(char **argv, t_sim *sim);
void	grab_forks(t_philo *philo);
void	return_forks(t_philo *philo);
size_t	get_time_in_ms(void);
void	printeatmsg(t_philo *philo, size_t garbage);
void	printsleepmsg(t_philo *philo, size_t garbage);
void	eat_sleep(t_philo *philo, size_t *start);
int		ft_usleep(size_t ms, t_sim *sim);
void	*monitoring(void *param);
void	*do_stuff(void *param);
int		make_threads(t_sim *sim);
int		destroy_mutexes(t_sim *sim);

#endif
