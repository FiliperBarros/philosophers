/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha-b <frocha-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:58:22 by frocha-b          #+#    #+#             */
/*   Updated: 2025/11/05 13:46:17 by frocha-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
int	main(void)
{
	pthread_t	th[4];
	int i;
	pthread_mutex_init(&mutex, NULL);

	for (i = 0; i < 4; i++)
	{
		
		if (0 != pthread_create(&th[i], NULL, &routine,  NULL))
		{
			perror("failed to create thread");
			return (2);
		}
		printf("thread %d has started \n", i);

	}
	for (i = 0; i < 4; i++)
	{
		if (0 != pthread_join(th[i], NULL))
			return (3);	
		printf("thread %d has finished \n", i);

	}
	pthread_mutex_destroy(&mutex);
	printf("Number of mails : %d", mails);
	return (0);
} */

int	main(int argc, char **argv)
{
	
	t_table table;
	check_args(argc, argv);
	(void) ft_memset(&table, '\0', sizeof(t_table));
	
	init_table(&table, argc, argv);
	init_philos(&table);
	init_threads(&table);
	return (0);
}