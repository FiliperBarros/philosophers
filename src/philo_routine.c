/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha-b <frocha-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:01:20 by frocha-b          #+#    #+#             */
/*   Updated: 2025/11/06 15:28:51 by frocha-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock((philo->right_fork));
	message(philo, EATING);
	usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleeping(t_philo *philo)
{
	message(philo, SLEEPING);
	usleep(philo->table->time_to_sleep * 1000);
}

void	thinking(t_philo *philo)
{
	message(philo, THINKING);
	usleep(2 * 1000);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	
	philo = (t_philo *) arg;

		/*attribute the correct time_of_last_meal*/
	philo->time_of_last_meal = philo->table->start_time;

	if (philo->id % 2 == 0)
		usleep(philo->table->time_to_eat * 1000); 

	while (1)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
void	message(t_philo *philo, char  *message)
{
	long	timestamp;
	
	timestamp = get_time_in_ms() - philo->table->start_time;
	pthread_mutex_lock(&philo->table->printf_mutex);
	printf("%ld ms  %d %s \n", timestamp, philo->id, message);
	pthread_mutex_unlock(&philo->table->printf_mutex);
	
}



