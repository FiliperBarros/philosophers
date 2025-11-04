/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha-b <frocha-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:58:22 by frocha-b          #+#    #+#             */
/*   Updated: 2025/11/04 16:24:47 by frocha-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/* 
int mails = 0;

pthread_mutex_t mutex;
void*	routine()
{
	for (int i = 0; i < 100000; i++){
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
	return (NULL);
}

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
	
	init_args(&table, argc, argv);

	
	init_philos(&table);
	init_threads(&table);
	

}