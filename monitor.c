#include "philo.h"


int print_status(t_data *data, int id, char *status)
{
	pthread_mutex_lock(&data->print_mutex);
	printf("%lld %d %s\n", get_time() - data->start_time, id, status);
	pthread_mutex_unlock(&data->print_mutex);
	return (0);
}

int check_all_ate(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].meal_check);
		if (data->philos[i].meals_eaten >= data->meals_count)
			data->all_ate++;
		pthread_mutex_unlock(&data->philos[i].meal_check);
		i++;
	}
	if (data->all_ate == data->num_philos)
		return (1);
	return (0);
}

int monitor(t_data *data)
{
	while (1)
	{
		for (int i = 0; i < data->num_philos; i++)
		{
			pthread_mutex_lock(&data->philos[i].meal_check);
			if (get_time() - data->philos[i].last_meal > data->time_to_die)
			{
				print_status(data, data->philos[i].id, "died");
				data->dead = 1;
				pthread_mutex_unlock(&data->philos[i].meal_check);
				return (1);
			}
			pthread_mutex_unlock(&data->philos[i].meal_check);
		}
		if(check_all_ate(data))
			return (1);
		// if (data->all_ate == data->num_philos)
		// 	return (1);
		usleep(100);
	}
	return (0);
}