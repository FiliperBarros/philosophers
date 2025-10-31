/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha-b <frocha-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:58:22 by frocha-b          #+#    #+#             */
/*   Updated: 2025/10/31 16:24:09 by frocha-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	pthread_t	t1, t2;
	pthread_mutex_init(&mutex, NULL);

	if (0 != pthread_create(&t1, NULL, &routine, NULL))
	return (1);
	if (0 != pthread_create(&t2, NULL, &routine,  NULL))
		return (2);
	if (0 != pthread_join(t1, NULL))
		return (3);
	if (0 != pthread_join(t2, NULL))
		return (4);
	pthread_mutex_destroy(&mutex);
	printf("Number of mails : %d", mails);
	return (0);
}
/* int	main(int argc, char **argv)
{
	t_data data;
	validate_args(argc, argv);
	init_args(&data, argc, argv);
} */