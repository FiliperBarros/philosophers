/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha-b <frocha-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:58:22 by frocha-b          #+#    #+#             */
/*   Updated: 2025/11/12 17:22:53 by frocha-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	
	t_table table;
	
	check_args(argc, argv);
	(void) ft_memset(&table, '\0', sizeof(t_table));
	
	init_table(&table, argc, argv);
	init_threads(&table);
		
	destroy(&table);
	return (0);
}