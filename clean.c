#include "philo.h";

int clear_data(t_data *data)
{
	int i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&data->philos[i].forks);
		pthread_mutex_destroy(&data->philos[i].print_mutex);
		i++;
	}
	free(data->philos);
	free(data->forks);
	pthread_mutex_destroy(&data->print_mutex);
	return (0);
}