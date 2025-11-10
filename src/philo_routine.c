/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha-b <frocha-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:01:20 by frocha-b          #+#    #+#             */
/*   Updated: 2025/11/10 12:17:48 by frocha-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	eating(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	
	message(philo, EATING, GREEN);
	
	usleep(philo->table->time_to_eat * 1000);
	
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleeping(t_philo *philo)
{
	message(philo, SLEEPING, BLUE);
	usleep(philo->table->time_to_sleep * 1000);
}

void	thinking(t_philo *philo)
{
	message(philo, THINKING, BRIGHT_YELLOW);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	
	philo = (t_philo *) arg;
	
	if (philo->id % 2 == 0)
		usleep((philo->table->time_to_eat) * 1000); 

	 while (1)
	{
		if (check_any_philo_dead(philo->table))
		  	return (NULL); 
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}


































