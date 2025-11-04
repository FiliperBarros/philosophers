/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha-b <frocha-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:35:16 by frocha-b          #+#    #+#             */
/*   Updated: 2025/11/04 15:55:49 by frocha-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;
	
	philo = (t_philo *) arg;
	return (NULL);
}


void	init_philos(t_table *table)
{
	int i;
	
	i = 0;
	table->philos = malloc(sizeof(t_philo) * table->nbr_of_philos);
	if (!table->philos)
		ft_exit_error("Failed to allocate philosophers.");
	while (i < table->nbr_of_philos)
	{
		table->philos[i].id = i;
		i++;
	}
}
/* ------------------------------ create threads ---------------------------- */
static void	create_threads(t_table *table)
{
	int i;
	
	i  = 0;
	while (++i < table->nbr_of_philos)
	{
		if (pthread_create(&table->philos[i].thread, 
			NULL, routine, &table->philos[i]) != 0)
				ft_exit_error("Failed to create thread.");	
		i++;
	}
}
/* ------------------------------ join threads ------------------------------ */
static void	join_threads(t_table *table)
{
	int i;
		
	i = 0;
	while (++i < table->nbr_of_philos)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			ft_exit_error("Thread join failed.");
		i++;
	}
}

void	init_threads(t_table *table)
{
	create_threads(table);
	join_threads(table);
}