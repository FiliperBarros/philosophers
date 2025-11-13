/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha-b <frocha-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 14:10:22 by frocha-b          #+#    #+#             */
/*   Updated: 2025/11/13 18:21:44 by frocha-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/******************************************************************************/
/*                              LIBRARIES                                     */
/******************************************************************************/
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>

/******************************************************************************/
/*                              ANSI COLORS                                   */
/******************************************************************************/
typedef enum t_color
{
	RED		= 31,
	GREEN	= 32,
	BLUE	= 34,
	WHITE	= 97,
	MAGENTA = 35,
	YELLOW	= 93,
}	t_ansiColor;

/******************************************************************************/
/*                              MESSAGES                                      */
/******************************************************************************/
# define FORKS    "has taken a fork"
# define EATING   "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED     " died"

# define MICRO_SECONDS 1000

/******************************************************************************/
/*                              STRUCTS                                       */
/******************************************************************************/
typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	long			last_meal;
	int				meals_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				nbr_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	int				nbr_of_meals_to_eat;

	int				simulation_should_end;

	pthread_mutex_t	monitoring_mutex;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	*forks;

	t_philo			*philos;
}	t_table;

int		simulation_should_end(t_table *table);
/******************************************************************************/
/*                              UTILS FUNCTIONS                               */
/******************************************************************************/
int		ft_is_digit(char c);
long	ft_atol(char *n);
void	ft_putstr_fd(char *s, int fd);
void	*ft_memset(void *s, int c, size_t n);
long	ft_get_time_in_ms(void);
void	ft_set_color(int code);
void	ft_reset_color(void);
void	ft_exit_error(char *message);
void	check_args(int argc, char **argv);

/******************************************************************************/
/*                              PHILOSOPHER ACTIONS                           */
/******************************************************************************/
void	take_forks(t_philo *philo);
void	drop_forks(t_philo *philo);
void	monitoring(t_philo *philo, char *message, int color);
void	*philo_routine(void *arg);

/******************************************************************************/
/*                              INITIALIZATION                                */
/******************************************************************************/
void	init_table(t_table *table, int argc, char **argv);
void	init_threads(t_table *table);
void	supervise(t_table *table);

/******************************************************************************/
/*                              CLEANUP                                       */
/******************************************************************************/
void	cleanup(t_table *table);

#endif
