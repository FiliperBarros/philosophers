/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha-b <frocha-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:58:22 by frocha-b          #+#    #+#             */
/*   Updated: 2025/11/13 14:15:58 by frocha-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_mutexes(t_table *table)
{
	int	i;

	i = -1;
	if (table->forks)
	{
		while (++i < table->nbr_of_philos)
			pthread_mutex_destroy(&table->forks[i]);
	}
	pthread_mutex_destroy(&table->last_meal_mutex);
	pthread_mutex_destroy(&table->monitoring_mutex);
}

void	cleanup(t_table *table)
{
	destroy_mutexes(table);
	if (table->forks)
		free(table->forks);
	if (table->philos)
		free(table->philos);
}

int	main(int argc, char **argv)
{
	t_table	table;

	check_args(argc, argv);
	(void) ft_memset(&table, 0, sizeof(t_table));
	init_table(&table, argc, argv);
	init_threads(&table);
	cleanup(&table);
	return (0);
}
