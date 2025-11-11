/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha-b <frocha-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:36:23 by frocha-b          #+#    #+#             */
/*   Updated: 2025/11/11 17:00:56 by frocha-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		/* SET_BOLD_COLOR(SOME);
		fprintf(stderr, "DBG: philo %d locked fork %p\n", philo->id, (void *)philo->left_fork); */
		pthread_mutex_lock((philo->right_fork));
		/* SET_BOLD_COLOR(SOME);
		fprintf(stderr, "DBG: philo %d unlocked fork %p\n", philo->id, (void *)philo->right_fork); */
	}
	else
	{
		pthread_mutex_lock((philo->right_fork));
		/* SET_BOLD_COLOR(SOME);
		fprintf(stderr, "DBG: philo %d unlocked fork %p\n", philo->id, (void *)philo->right_fork); */
		pthread_mutex_lock(philo->left_fork);
		/* SET_BOLD_COLOR(SOME);
		fprintf(stderr, "DBG: philo %d unlocked fork %p\n", philo->id, (void *)philo->left_fork); */
	}
	monitoring(philo, FORKS, WHITE);
	monitoring(philo, FORKS, WHITE);
}

void	drop_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		/* SET_BOLD_COLOR(SOME);
		fprintf(stderr, "DBG: philo %d unlocked fork %p\n", philo->id, (void *)philo->left_fork); */
		pthread_mutex_unlock((philo->right_fork));
		/* SET_BOLD_COLOR(SOME);
		fprintf(stderr, "DBG: philo %d unlocked fork %p\n", philo->id, (void *)philo->right_fork); */
	}
	else
	{
		pthread_mutex_unlock((philo->right_fork));
		/* SET_BOLD_COLOR(SOME);
		fprintf(stderr, "DBG: philo %d unlocked fork %p\n", philo->id, (void *)philo->right_fork); */
		pthread_mutex_unlock(philo->left_fork);
		/* SET_BOLD_COLOR(SOME);
		fprintf(stderr, "DBG: philo %d unlocked fork %p\n", philo->id, (void *)philo->left_fork); */
	}
}
void	monitoring(t_philo *philo, char  *message, int ansi_color)
{
	long	timestamp;

	pthread_mutex_lock(&philo->table->monitoring_mutex);
	if(philo->table->simulation_should_end)
	{
		pthread_mutex_unlock(&philo->table->monitoring_mutex);
		return ;
	}
	
	timestamp = get_time_in_ms() - philo->table->start_time;
	SET_BOLD_COLOR(ansi_color);
	printf("%ld ms  %d %s \n", timestamp, philo->id, message);
	pthread_mutex_unlock(&philo->table->monitoring_mutex);
	
}
