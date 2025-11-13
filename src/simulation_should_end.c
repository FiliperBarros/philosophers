/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_should_end.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha-b <frocha-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 18:20:13 by frocha-b          #+#    #+#             */
/*   Updated: 2025/11/13 18:20:32 by frocha-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	simulation_should_end(t_table *table)
{
	int	end_flag;

	end_flag = 0;
	pthread_mutex_lock(&table->monitoring_mutex);
	if (table->simulation_should_end)
		end_flag = 1;
	pthread_mutex_unlock(&table->monitoring_mutex);
	return (end_flag);
}
