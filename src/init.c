/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha-b <frocha-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:35:16 by frocha-b          #+#    #+#             */
/*   Updated: 2025/11/05 13:42:59 by frocha-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(t_table *table)
{
	int	i;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nbr_of_philos);
	if (!table->forks)
		ft_exit_error("Failed to allocate forks.");
	i = 0;
	while (i < table->nbr_of_philos)
	{
		if(pthread_mutex_init(table->forks,NULL) != 0)
			ft_exit_error("Failed to initialize fork mutex.");
		i++;
	}
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
		table->philos[i].id = i + 1 ;
		table->philos[i].meals_eaten = 0;
		table->philos[i].time_of_last_meal = get_time_in_ms();
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1) % table->nbr_of_philos];
		table->philos[i].table = table;
		i++;
	}
}

/* ------------------------------ create threads ---------------------------- */
static void	create_threads(t_table *table)
{
	int i;
	
	i  = 0;
	while (i < table->nbr_of_philos)
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
	while (i < table->nbr_of_philos)
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
