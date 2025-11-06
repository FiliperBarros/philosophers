/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha-b <frocha-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:13:53 by frocha-b          #+#    #+#             */
/*   Updated: 2025/11/06 15:40:51 by frocha-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_table(t_table *table, int argc, char **argv)
{
	table->nbr_of_philos = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	table->philo_dead = 0;
	pthread_mutex_init(&table->nbr_of_meals_eaten, NULL);
	pthread_mutex_init(&table->printf_mutex, NULL);
	pthread_mutex_init(&table->died_mutex, NULL);
	init_forks(table);
	init_philos(table);
	if (argc == 6)
		table->nbr_of_meals_to_eat	= ft_atol(argv[5]);
	else
		table->nbr_of_meals_to_eat	= -1;
}

void	init_forks(t_table *table)
{
	int	i;
	
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nbr_of_philos);
	if (!table->forks)
		ft_exit_error("Failed to allocate forks.");
	i = 0;
	while (i < table->nbr_of_philos)
	{
		if(pthread_mutex_init(&table->forks[i],NULL) != 0)
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
		table->philos[i].time_of_last_meal = table->start_time;	
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1) % table->nbr_of_philos];
		pthread_mutex_init(&table->philos[i].last_meal_mutex,NULL);
		table->philos[i].table = table;
		i++;
	}
}
