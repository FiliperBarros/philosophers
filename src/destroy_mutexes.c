/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_mutexes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha-b <frocha-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:08:58 by frocha-b          #+#    #+#             */
/*   Updated: 2025/11/12 17:28:03 by frocha-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy(t_table *table)
{
	int i = -1;

	// if(table->monitoring_mutex)
		pthread_mutex_destroy(&table->monitoring_mutex);
	if (table->forks)
		while (++i < table->nbr_of_philos)
			pthread_mutex_destroy(&table->forks[i]);
	if (table->philos)
		free(table->philos);
}