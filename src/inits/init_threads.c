/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha-b <frocha-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:35:16 by frocha-b          #+#    #+#             */
/*   Updated: 2025/11/12 18:09:51 by frocha-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	create_threads(t_table *table)
{
	int i;
	
	i  = 0;
	table->start_time = get_time_in_ms();
	while (i < table->nbr_of_philos)
	{
		table->philos[i].last_meal = get_time_in_ms();
		if (pthread_create(&table->philos[i].thread, 
			NULL, philo_routine, &table->philos[i]) != 0)
				ft_exit_error("Failed to create thread.");	
		i++;
	}
}
static void	join_threads(t_table *table)
{
	int i;
		
	i = 0;
	while (i < table->nbr_of_philos)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			ft_exit_error("Failed to join thread.");
		i++;
	}
}

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
static void supervise(t_table *table)
{
	int i;
	int satisfied_philos;
	
	while (1)
	{
		i = -1;
		satisfied_philos = 0;
		pthread_mutex_lock(&table->monitoring_mutex);
		while (++i < table->nbr_of_philos)
		{
			if (is_philo_dead(table, &table->philos[i], &satisfied_philos))
			   return ;
		}
		if (satisfied_philos == table->nbr_of_philos)
			   return (all_have_eaten(table));
		pthread_mutex_unlock(&table->monitoring_mutex);
		usleep(MICRO_SECONDS);
	}
}
void	init_threads(t_table *table)
{
	create_threads(table);
	supervise(table);	
	join_threads(table);
}
