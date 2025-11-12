/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervise.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha-b <frocha-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:23:49 by frocha-b          #+#    #+#             */
/*   Updated: 2025/11/12 18:39:06 by frocha-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int  is_philo_dead(t_table *table, t_philo *philo, int *satisfied_philos)
{
	if (table->nbr_of_meals_to_eat > 0 && philo->meals_eaten >= table->nbr_of_meals_to_eat )
		*satisfied_philos += 1;
	pthread_mutex_lock(&philo->table->last_meal_mutex);
	if (starved(philo))
	{
		pthread_mutex_unlock(&philo->table->last_meal_mutex);
		pthread_mutex_unlock(&table->monitoring_mutex);
		monitoring(philo, DIED, RED);
		pthread_mutex_lock(&table->monitoring_mutex);
		table->simulation_should_end = 1;
		pthread_mutex_unlock(&table->monitoring_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->last_meal_mutex);
	return (0);
}


/* Function to watch philo's activities */
void supervise(t_table *table)
{
	int i;
	int satisfied_philos;
	
	while (1)
	{
		satisfied_philos = 0;
		i = -1;
		pthread_mutex_lock(&table->monitoring_mutex);
		while (++i < table->nbr_of_philos)
		{
			if (is_philo_dead(table, &table->philos[i], &satisfied_philos))
			   return ;
		}
		pthread_mutex_unlock(&table->monitoring_mutex);
		if (satisfied_philos == table->nbr_of_philos)
		{
			all_have_eaten(table);
			return ;
		}
		usleep(MICRO_SECONDS);
	}
}