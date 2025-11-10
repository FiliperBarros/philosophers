/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha-b <frocha-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:58:33 by frocha-b          #+#    #+#             */
/*   Updated: 2025/11/10 11:49:57 by frocha-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#define MIN_TIME 60
#define EVEN_PHILOS_SLEEP 500

/******************************************************************************/
/*                               LIBRARY                                      */
/******************************************************************************/
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>


/******************************************************************************/
/*                            	 ENUM	                                      */
/******************************************************************************/
typedef enum {
    RED          = 31,
    GREEN        = 32,
    BLUE         = 34,
    WHITE        = 37,
    BRIGHT_YELLOW  = 93,
} AnsiColor;

/******************************************************************************/
/*                            	DEFINE	                                      */
/******************************************************************************/
#define SET_BOLD_COLOR(code)   printf("\033[1;%dm", code)

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
	long			last_meal;
	int				meals_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	count_meals_mutex;
	struct s_table	*table;
	
}				t_philo;

typedef struct s_table
{
	int				nbr_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	int				nbr_of_meals_to_eat;
	int				philo_dead;
	pthread_mutex_t	nbr_of_meals_eaten_mutex;
	pthread_mutex_t printf_mutex;
	pthread_mutex_t died_mutex;
	pthread_mutex_t	*forks;
	struct s_philo	*philos;
}				t_table;

int 	check_any_philo_dead(t_table *table);
void	destroy_all_mutexes(t_table	*table);
void	take_forks(t_philo *philo);
void	message(t_philo *philo, char  *message, int color);
void	*philo_routine(void *arg);

/******************************************************************************/
/*                               INIT                                        */
/******************************************************************************/
void	init_table(t_table *table, int argc, char **argv);
void	init_philos(t_table *table);
void	init_forks(t_table *table);
void	init_mutexes(t_table *table);
void	init_threads(t_table *table);

/******************************************************************************/
/*                               UTILS                                        */
/******************************************************************************/
void	*ft_memset(void *s, int c, size_t n);
int		ft_is_digit(char c);
long	ft_atol(char *n);
void	ft_exit_error(char *message);
void	ft_putstr_fd(char *s, int fd);
long	get_time_in_ms();

void	check_args(int argc, char **argv);

#endif