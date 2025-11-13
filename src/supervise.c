/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervise.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha-b <frocha-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:23:49 by frocha-b          #+#    #+#             */
/*   Updated: 2025/11/13 18:13:18 by frocha-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Check if a philosopher has starved */
static int	ft_starved(t_philo *philo)
{
	long	now;
	long	diff;

	now = ft_get_time_in_ms();
	diff = now - philo->last_meal;
	return (diff >= philo->table->time_to_die);
}

/* Announce that all philosophers have eaten enough */
static void	ft_all_have_eaten(t_table *table)
{
	pthread_mutex_lock(&table->monitoring_mutex);
	table->simulation_should_end = 1;
	ft_set_color(MAGENTA);
	printf("Every Philosopher had %d meals!\n", table->nbr_of_meals_to_eat);
	ft_reset_color();
	pthread_mutex_unlock(&table->monitoring_mutex);
}

/* Check if a philosopher is dead or satisfied with meals */
static int	ft_is_philo_dead(t_philo *philo, int *satisfied_philos)
{
	if (philo->table->nbr_of_meals_to_eat > 0
		&& philo->meals_eaten >= philo->table->nbr_of_meals_to_eat)
		*satisfied_philos += 1;
	pthread_mutex_lock(&philo->table->last_meal_mutex);
	if (ft_starved(philo))
	{
		pthread_mutex_unlock(&philo->table->last_meal_mutex);
		pthread_mutex_unlock(&philo->table->monitoring_mutex);
		monitoring(philo, DIED, RED);
		pthread_mutex_lock(&philo->table->monitoring_mutex);
		philo->table->simulation_should_end = 1;
		pthread_mutex_unlock(&philo->table->monitoring_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->last_meal_mutex);
	return (0);
}

/* Supervise all philosophers to check for death or meal completion */
void	supervise(t_table *table)
{
	int	i;
	int	satisfied_philos;

	while (1)
	{
		satisfied_philos = 0;
		i = -1;
		pthread_mutex_lock(&table->monitoring_mutex);
		while (++i < table->nbr_of_philos)
		{
			if (ft_is_philo_dead(&table->philos[i],
					&satisfied_philos))
			{
				return ;
			}
		}
		pthread_mutex_unlock(&table->monitoring_mutex);
		if (satisfied_philos == table->nbr_of_philos)
		{
			ft_all_have_eaten(table);
			return ;
		}
		usleep(MICRO_SECONDS);
	}
}
