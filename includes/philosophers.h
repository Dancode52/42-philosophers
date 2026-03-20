/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 10:43:03 by dlanehar          #+#    #+#             */
/*   Updated: 2026/03/20 08:40:12 by dlanehar         ###   ########.fr       */
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

typedef enum e_msg_type
{
    MSG_FORK,
    MSG_EAT,
    MSG_SLEEP,
    MSG_THINK,
    MSG_DIED
} t_msg_type;

typedef	struct	s_philo
{
	int			index;
	int			id;
	pthread_t	philo_t;
	size_t		last_meal;
	int			meals_eaten;
	t_sim		*sim;
}	t_philo;

typedef struct s_sim
{
	int				no_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				no_of_meals;
	int				death;
	size_t			progstart;
	t_philo			*philos;
	pthread_t		monitor;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	*meal_mutex;
	pthread_mutex_t	printf_mutex;
	pthread_mutex_t	death_mutex;
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
void	*philo_routine(void *param);
int		make_threads(t_sim *sim);
int		destroy_mutexes(t_sim *sim);
void	free_and_destroy(t_sim *sim, pthread_mutex_t *ptr, int j);
int		death_checker(t_sim *sim);
int		meal_checker(t_sim *sim, int index);
int		init_mutexes(t_sim *sim);
int		mutex_init_loop(t_sim *sim, pthread_mutex_t *ptr);
int		ph_eating(t_philo *philos, int index);
void	odd_eat(t_philo *philos, int index);
void	even_eat(t_philo *philos, int index);
void	print_msg(t_philo *philos, t_msg_type type);

#endif
