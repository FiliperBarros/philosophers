/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha-b <frocha-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:35:16 by frocha-b          #+#    #+#             */
/*   Updated: 2025/11/12 18:26:45 by frocha-b         ###   ########.fr       */
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

void	init_threads(t_table *table)
{
	create_threads(table);
	supervise(table);	
	join_threads(table);
}
