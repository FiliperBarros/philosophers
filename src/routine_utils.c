/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha-b <frocha-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:36:23 by frocha-b          #+#    #+#             */
/*   Updated: 2025/11/10 13:53:14 by frocha-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		monitoring(philo, FORKS, WHITE);
		pthread_mutex_lock((philo->right_fork));
		monitoring(philo, FORKS, WHITE);
	}
	else
	{
		pthread_mutex_lock((philo->right_fork));
		monitoring(philo, FORKS, WHITE);
		pthread_mutex_lock(philo->left_fork);
		monitoring(philo, FORKS, WHITE);
	}
}

void	drop_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		monitoring(philo, FORKS, WHITE);
		pthread_mutex_unlock((philo->right_fork));
		monitoring(philo, FORKS, WHITE);
	}
	else
	{
		pthread_mutex_unlock((philo->right_fork));
		monitoring(philo, FORKS, WHITE);
		pthread_mutex_unlock(philo->left_fork);
		monitoring(philo, FORKS, WHITE);
	}
	
}
void	monitoring(t_philo *philo, char  *message, int ansi_color)
{
	long	timestamp;
	
	pthread_mutex_lock(&philo->table->died_mutex);
	if(philo->table->philo_dead)
	{
		pthread_mutex_unlock(&philo->table->died_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->table->died_mutex);
	
	timestamp = get_time_in_ms() - philo->table->start_time;
	pthread_mutex_lock(&philo->table->printf_mutex);
	SET_BOLD_COLOR(ansi_color);
	printf("%ld ms  %d %s \n", timestamp, philo->id, message);
	pthread_mutex_unlock(&philo->table->printf_mutex);
	
}

int monitor_philo_dead(t_table *table)
{

	int 	i;
	long	now;

	i = -1;

	pthread_mutex_lock(&table->died_mutex);
	if (table->philo_dead == 1)
	{	
		pthread_mutex_unlock(&table->died_mutex);
		return (1);
	}
	pthread_mutex_unlock(&table->died_mutex);
	while (++i < table->nbr_of_philos)
	{
		pthread_mutex_lock(&table->philos[i].last_meal_mutex);
		now = get_time_in_ms();
		if (now - table->philos[i].last_meal >= table->time_to_die)
		{	
			monitoring(&table->philos[i], DIED, RED);
			pthread_mutex_lock(&table->died_mutex);
			table->philo_dead = 1;
			pthread_mutex_unlock(&table->died_mutex);
			pthread_mutex_unlock(&table->philos[i].last_meal_mutex);
			return (1);
		}
		pthread_mutex_unlock(&table->philos[i].last_meal_mutex);
	}
	return (0);
}
