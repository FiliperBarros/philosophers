/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha-b <frocha-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:35:16 by frocha-b          #+#    #+#             */
/*   Updated: 2025/11/07 13:15:06 by frocha-b         ###   ########.fr       */
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

void	init_threads(t_table *table)
{
	create_threads(table);
	join_threads(table);
}
