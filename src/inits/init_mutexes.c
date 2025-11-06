/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha-b <frocha-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:54:32 by frocha-b          #+#    #+#             */
/*   Updated: 2025/11/06 16:29:15 by frocha-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static void	init_table_mutexes(t_table *table)
{
	pthread_mutex_init(&table->nbr_of_meals_eaten, NULL);
	pthread_mutex_init(&table->printf_mutex, NULL);
	pthread_mutex_init(&table->died_mutex, NULL);
}

static void	init_philos_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_of_philos)
	{
		pthread_mutex_init(&table->philos[i].last_meal_mutex,NULL);
		pthread_mutex_init(&table->philos[i].count_meals_mutex, NULL);
		i++;
	}
}

void	init_mutexes(t_table *table)
{
	init_table_mutexes(table);
	init_philos_mutexes(table);
}