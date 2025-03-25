#include "philo.h"


int print_status(t_data *data, int id, char *status)
{
	pthread_mutex_lock(&data->print_mutex);
	printf("%lld %d %s\n", ft_get_time(data) - data->start_time, id, status);
	pthread_mutex_unlock(&data->print_mutex);
	return (0);
}

int check_all_ate(t_data *data)
{
	int i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_lock(&data->meal_check);
		if (data->philos[i].meals_eaten >= data->meals_count)
			data->all_ate++;
		pthread_mutex_unlock(&data->meal_check);
		i++;
	}
	if (data->all_ate == data->philo_count)
		return (1);
	return (0);
}

int monitor(t_data *data)
{
	while (1)
	{
		printf("monitor started %d\n", data->one_dead);
		for (int i = 0; i < data->philo_count; i++)
		{
			pthread_mutex_lock(&data->meal_check);
			if (ft_get_time(data) - data->philos[i].last_meal > data->time_to_die)
			{
				print_msg(data, &data->philos[i], "died");
				data->one_dead = 1;
				pthread_mutex_unlock(&data->meal_check);
				return (1);
			}
			pthread_mutex_unlock(&data->meal_check);
		}
		if(check_all_ate(data))
			return (1);
		// if (data->all_ate == data->num_philos)
		// 	return (1);
		usleep(100);
	}
	return (0);
}