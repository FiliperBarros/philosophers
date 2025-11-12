/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha-b <frocha-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:58:33 by frocha-b          #+#    #+#             */
/*   Updated: 2025/11/12 18:44:49 by frocha-b         ###   ########.fr       */
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
    RED          	= 31,
    GREEN        	= 32,
    BLUE         	= 34,
    WHITE        	= 37,
    BRIGHT_YELLOW  	= 93,
	MAGENTA			= 35,
} AnsiColor;

/******************************************************************************/
/*                            	DEFINE	                                      */
/******************************************************************************/

# define FORKS "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED " died"

#define MICRO_SECONDS 1000

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
	int				simulation_should_end;
	pthread_mutex_t	monitoring_mutex;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	*forks;
	struct s_philo	*philos;
}				t_table;


void set_bold_color(int code);
void supervise(t_table *table);

int		monitor_philo_dead(t_table *table);
void	destroy(t_table	*table);
void	take_forks(t_philo *philo);
void	drop_forks(t_philo *philo);
void	monitoring(t_philo *philo, char  *message, int color);
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



static inline int starved(t_philo *philo)
{
    long now = get_time_in_ms();
    long diff = now - philo->last_meal;
    return (diff > philo->table->time_to_die + 2); // +2 ms tolerance
}

static inline void all_have_eaten(t_table *table)
{
	pthread_mutex_lock(&table->monitoring_mutex);
	table->simulation_should_end = 1;
	set_bold_color(MAGENTA);
	printf("Every Philosopher had %d meals!\n", table->nbr_of_meals_to_eat);
	pthread_mutex_unlock(&table->monitoring_mutex);
}
#endif