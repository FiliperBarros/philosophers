/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha-b <frocha-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:01:20 by frocha-b          #+#    #+#             */
/*   Updated: 2025/11/10 17:57:45 by frocha-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->table->last_meal_mutex);
	philo->last_meal = get_time_in_ms();
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&philo->table->last_meal_mutex);
	
	monitoring(philo, EATING, GREEN);
	
	usleep(philo->table->time_to_eat * MICRO_SECONDS);
	drop_forks(philo);
}

void	sleeping(t_philo *philo)
{
	monitoring(philo, SLEEPING, BLUE);
	usleep(philo->table->time_to_sleep * MICRO_SECONDS);
}

void	thinking(t_philo *philo)
{
	monitoring(philo, THINKING, BRIGHT_YELLOW);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	
	philo = (t_philo *) arg;
	
	if (philo->table->nbr_of_philos == 1)
		monitoring(philo, FORKS, WHITE);
	 while (1)
	{
		pthread_mutex_lock(&philo->table->monitoring_mutex);
		if (philo->table->simulation_should_end)
		{
	        pthread_mutex_lock(&philo->table->monitoring_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->table->monitoring_mutex);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}


































