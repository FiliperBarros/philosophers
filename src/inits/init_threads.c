/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha-b <frocha-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:35:16 by frocha-b          #+#    #+#             */
/*   Updated: 2025/11/10 17:51:35 by frocha-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	give_start_meal_to_philos(t_philo *philo)
{
	int i;

	i = -1;
	while (++i < philo->table->nbr_of_philos)
		philo[i].last_meal = get_time_in_ms();
}

static void	create_threads(t_table *table)
{
	int i;
	
	i  = 0;
			/*Get a precise start_time*/
	table->start_time = get_time_in_ms();
	while (i < table->nbr_of_philos)
	{
		give_start_meal_to_philos(table->philos);
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
	if (table->nbr_of_meals_to_eat > 0 && table->nbr_of_meals_to_eat > philo->meals_eaten )
	     *satisfied_philos += 1;
	if (starved(philo))
	{
		pthread_mutex_unlock(&table->monitoring_mutex);
		monitoring(philo, DIED, RED);
		pthread_mutex_lock(&table->monitoring_mutex);
		table->simulation_should_end = 1;
		pthread_mutex_unlock(&table->monitoring_mutex);
        return (1);
	}
	return (0);
}


/* Function to watch philo's activities */
static void supervise(t_table *table)
{
	int i;
	int satisfied_philos;

    satisfied_philos = 0;
	while (1)
	{
		i = -1;
		pthread_mutex_lock(&table->monitoring_mutex);
		while (++i < table->nbr_of_philos)
		{
			if (is_philo_dead(table, &table->philos[i], &satisfied_philos))
			   return ;
		}
		if (satisfied_philos == table->nbr_of_philos)
			   return (all_have_eaten(table));
		pthread_mutex_unlock(&table->monitoring_mutex);
	}
}
void	init_threads(t_table *table)
{
	create_threads(table);
	supervise(table);
	join_threads(table);
}
