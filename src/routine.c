#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;
	
	philo = (t_philo *) arg;

	pthread_mutex_lock(&philo->table->printf_mutex);
	printf("Philo %d is eating\n", philo->id);
	pthread_mutex_unlock(&philo->table->printf_mutex);
	return (NULL);
}



