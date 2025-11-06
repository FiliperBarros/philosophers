/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha-b <frocha-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:01:20 by frocha-b          #+#    #+#             */
/*   Updated: 2025/11/06 17:29:52 by frocha-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	eating(t_philo *philo)
{
	take_forks(philo);
	message(philo, EATING, GREEN);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->last_meal_mutex);
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
	usleep(2 * 1000);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int		i = 0;
	
	philo = (t_philo *) arg;

		/*attribute the correct time_of_last_meal*/
	philo->last_meal = philo->table->start_time;

	if (philo->id % 2 == 0)
		usleep(philo->table->time_to_eat * 1000); 

	while (i < 5)
	{
		// if (check_any_philo_dead(philo->table))
		// 	return (NULL);
		eating(philo);
		sleeping(philo);
		thinking(philo);
		i++;
	}
	return (NULL);
}


































