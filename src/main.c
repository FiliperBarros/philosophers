/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha-b <frocha-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:58:22 by frocha-b          #+#    #+#             */
/*   Updated: 2025/11/10 17:31:29 by frocha-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	
	t_table table;
	
	check_args(argc, argv);
	(void) ft_memset(&table, '\0', sizeof(t_table));
	
	init_table(&table, argc, argv);

	/* int i = -1;
	table.start_time = get_time_in_ms();
	while (++i < 5)
	{
	   table.philos[i].last_meal = get_time_in_ms();
	   philo_routine(&table.philos[i]);
    } */
	init_threads(&table);	
	destroy(&table);
	free(table.philos);
	free(table.forks);
	return (0);
}