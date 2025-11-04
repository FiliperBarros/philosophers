/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha-b <frocha-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:58:33 by frocha-b          #+#    #+#             */
/*   Updated: 2025/11/04 16:52:28 by frocha-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#define MIN_TIME 60

/******************************************************************************/
/*                             Libraries                                      */
/******************************************************************************/
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>

# define FORKS "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED " died\n"

/******************************************************************************/
/*                               STRUCTS                                      */
/******************************************************************************/
typedef	struct s_philo
{
	int				id;
	pthread_t 		thread;
	pthread_mutex_t	*fork_mutex;
	long			time_of_last_meal;
	int				meals_eaten;
}				t_philo;

typedef struct s_table
{
	int				nbr_of_philos;
	long			start_time;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nbr_of_meals_to_eat;
	pthread_mutex_t	nbr_of_meals_eaten;
	struct s_philo	*philos;
}				t_table;

void	init_threads(t_table *table);
void	init_philos(t_table *table);

/******************************************************************************/
/*                               UTILS                                        */
/******************************************************************************/
void	*ft_memset(void *s, int c, size_t n);
int		ft_is_digit(char c);
long	ft_atol(char *n);
void	ft_exit_error(char *message);
void	ft_putstr_fd(char *s, int fd);
long	get_time_in_ms();

/******************************************************************************/
/*                               PARSER                                       */
/******************************************************************************/
void	check_args(int argc, char **argv);
void	init_args(t_table *table, int argc, char **argv);
#endif