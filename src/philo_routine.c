#include "philo.h"

/* Prints a message with timestamp if simulation is ongoing */
void	monitoring(t_philo *philo, char *message, int ansi_color)
{
	long	timestamp;

	pthread_mutex_lock(&philo->table->monitoring_mutex);
	if (philo->table->simulation_should_end)
	{
		pthread_mutex_unlock(&philo->table->monitoring_mutex);
		return ;
	}
	timestamp = ft_get_time_in_ms() - philo->table->start_time;
	ft_set_bold_color(ansi_color);
	printf("%ld ms  %d %s\n", timestamp, philo->id, message);
	pthread_mutex_unlock(&philo->table->monitoring_mutex);
}

/* Philosopher takes forks, eats, updates last meal and meal count */
void	eating(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->table->last_meal_mutex);
	philo->last_meal = ft_get_time_in_ms();
	pthread_mutex_unlock(&philo->table->last_meal_mutex);
	monitoring(philo, EATING, GREEN);

	long start_eat = ft_get_time_in_ms();
	while (ft_get_time_in_ms() - start_eat < philo->table->time_to_eat)
	{
		pthread_mutex_lock(&philo->table->monitoring_mutex);
		if (philo->table->simulation_should_end)
		{
			pthread_mutex_unlock(&philo->table->monitoring_mutex);
			drop_forks(philo);
			return ;
		}
		pthread_mutex_unlock(&philo->table->monitoring_mutex);
		usleep(500); // small sleep to be responsive
	}

	pthread_mutex_lock(&philo->table->last_meal_mutex);
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&philo->table->last_meal_mutex);
	drop_forks(philo);
}

/* Smart sleep with death check */
void	smart_sleep(t_philo *philo, long duration)
{
	long	start = ft_get_time_in_ms();

	while (ft_get_time_in_ms() - start < duration)
	{
		pthread_mutex_lock(&philo->table->monitoring_mutex);
		if (philo->table->simulation_should_end)
		{
			pthread_mutex_unlock(&philo->table->monitoring_mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->table->monitoring_mutex);
		usleep(500);
	}
}

/* Philosopher sleeps for configured time */
void	sleeping(t_philo *philo)
{
	monitoring(philo, SLEEPING, BLUE);
	smart_sleep(philo, philo->table->time_to_sleep);
}

/* Philosopher thinks */
void	thinking(t_philo *philo)
{
	monitoring(philo, THINKING, BRIGHT_YELLOW);
}

/* Main routine for each philosopher thread */
void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->table->nbr_of_philos == 1)
	{
		monitoring(philo, FORKS, WHITE);
		smart_sleep(philo, philo->table->time_to_die);
		return (NULL);
	}

	if (philo->id % 2 == 0)
		usleep(1000); // stagger even philosophers

	while (1)
	{
		pthread_mutex_lock(&philo->table->monitoring_mutex);
		if (philo->table->simulation_should_end)
		{
			pthread_mutex_unlock(&philo->table->monitoring_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->table->monitoring_mutex);

		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
