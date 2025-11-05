/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha-b <frocha-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:13:53 by frocha-b          #+#    #+#             */
/*   Updated: 2025/11/05 15:03:55 by frocha-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_table(t_table *table, int argc, char **argv)
{
	table->nbr_of_philos = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	table->start_time = get_time_in_ms();
	if (argc == 6)
		table->nbr_of_meals_to_eat	= ft_atol(argv[5]);
	else
		table->nbr_of_meals_to_eat	= -1;
	table->philo_dead = 0;
	pthread_mutex_init(&table->nbr_of_meals_eaten, NULL);
	pthread_mutex_init(&table->printf_mutex, NULL);
	init_forks(table);
	init_philos(table);
}
