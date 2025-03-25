#include "philo.h"

int assign_forks(t_data *data, t_philo *philo, int philo_count)
{
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &data->forks[philo->id - 1];
		philo->second_fork = &data->forks[(philo->id) % philo_count];
	}
	else
	{
		philo->first_fork = &data->forks[(philo->id) % philo_count];
		philo->second_fork = &data->forks[philo->id - 1];
	}
	// if (philo->id % 2 == 0)
	// {
	// 	philo->first_fork = philo->id - 1;
	// 	philo->second_fork = (philo->id) % philo_count;
	// }
	// else
	// {
	// 	philo->first_fork = (philo->id) % philo_count;
	// 	philo->second_fork = philo->id - 1;
	// }
	// philo->first_fork = philo->id - 1;
	// philo->second_fork = (philo->id) % philo_count;
	return (0);
}

int sleeping(t_data *data, t_philo *philo)
{
	long long	time;


	time = ft_get_time(philo->data);
	pthread_mutex_lock(&data->print_mutex);
	print_msg(data, philo, "is sleeping");
	pthread_mutex_unlock(&data->print_mutex);
	ft_usleep(data->time_to_sleep, data);
	return (0);
}

int eating(t_data *data, t_philo *philo)
{
	long long	time;

	time = ft_get_time(philo->data);
	pthread_mutex_lock(&data->print_mutex);
	print_msg(data, philo, "is eating");
	pthread_mutex_unlock(&data->print_mutex);
	ft_usleep(data->time_to_eat, data);
	pthread_mutex_lock(&data->meal_check);
	philo->meals_eaten++;
	if (philo->meals_eaten == data->meals_count)
		data->all_ate = 1;
	pthread_mutex_unlock(&data->meal_check);
	return (0);
}

int start_routine(t_data *data, t_philo *philo)
{
//	int i;

	while (1)
	{
		pthread_mutex_lock(philo->first_fork);
		pthread_mutex_lock(philo->second_fork);
		eating(data, philo);
		pthread_mutex_unlock(philo->first_fork);
		pthread_mutex_unlock(philo->second_fork);
		sleeping(data, philo);
	}
}

void *routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	start_routine(philo->data, philo);
	return (NULL);
}