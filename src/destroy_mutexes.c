/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_mutexes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha-b <frocha-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:08:58 by frocha-b          #+#    #+#             */
/*   Updated: 2025/11/07 12:34:59 by frocha-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_philos_mutexes(t_table *table)
{
	int i = -1;

	while (++i < table->nbr_of_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philos[i].last_meal_mutex);
		pthread_mutex_destroy(&table->philos[i].count_meals_mutex);
	}
}

static void	destroy_table_mutexes(t_table *table)
{
	pthread_mutex_destroy(&table->nbr_of_meals_eaten_mutex);
	pthread_mutex_destroy(&table->printf_mutex);
	pthread_mutex_destroy(&table->died_mutex);
}
void	destroy_all_mutexes(t_table	*table)
{
	destroy_philos_mutexes(table);
	destroy_table_mutexes(table);
}