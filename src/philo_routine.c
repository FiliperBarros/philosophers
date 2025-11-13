/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha-b <frocha-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:01:20 by frocha-b          #+#    #+#             */
/*   Updated: 2025/11/13 18:27:26 by frocha-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Prints a message with timestamp if simulation is ongoing */
void	monitoring(t_philo *philo, char *message, int ansi_color)
{
	long	timestamp;

	if (simulation_should_end(philo->table))
		return ;
	timestamp = ft_get_time_in_ms() - philo->table->start_time;
	ft_set_color(ansi_color);
	printf("%5ld ms  %-1d  %-10s\n", timestamp, philo->id, message);
	ft_reset_color();
}

/* Philosopher takes forks, eats, updates last meal and meal count */
void	eating(t_philo *philo)
{
	long	time;

	time = philo->table->time_to_eat;
	if (philo->table->time_to_eat > philo->table->time_to_die)
		time = philo->table->time_to_die;
	take_forks(philo);
	pthread_mutex_lock(&philo->table->last_meal_mutex);
	philo->last_meal = ft_get_time_in_ms();
	pthread_mutex_unlock(&philo->table->last_meal_mutex);
	monitoring(philo, EATING, GREEN);
	usleep(time * MICRO_SECONDS);
	pthread_mutex_lock(&philo->table->last_meal_mutex);
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&philo->table->last_meal_mutex);
	drop_forks(philo);
}

/* Philosopher sleeps for configured time */
void	sleeping(t_philo *philo)
{
	long	time;

	time = philo->table->time_to_sleep;
	if (philo->table->time_to_sleep > philo->table->time_to_die)
		time = philo->table->time_to_die;
	monitoring(philo, SLEEPING, BLUE);
	usleep(time * MICRO_SECONDS);
}

/* Philosopher thinks */
void	thinking(t_philo *philo)
{
	monitoring(philo, THINKING, YELLOW);
}

/* Main routine for each philosopher thread */
void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->table->nbr_of_philos == 1)
		return (monitoring(philo, FORKS, WHITE), NULL);
	if (philo->id % 2 == 0)
		usleep(MICRO_SECONDS);
	while (!simulation_should_end(philo->table))
	{
		eating(philo);
		if (simulation_should_end(philo->table) == 1)
			break ;
		sleeping(philo);
		if (simulation_should_end(philo->table))
			break ;
		thinking(philo);
		if (simulation_should_end(philo->table))
			break ;
		if (philo->id % 2 != 0 && philo->table->nbr_of_philos % 2 != 0)
			usleep(MICRO_SECONDS);
	}
	return (NULL);
}
