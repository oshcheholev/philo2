#include "philo.h"

int init_forks(t_philo *philos, int philo_count)
{
	int i;

	i = 0;
	while (i < philo_count)
	{
		philos[i].left_fork = i;
		philos[i].right_fork = (i + 1) % philo_count;
		i++;
	}
	return (0);
}

int init_mutex(t_philo *philos, int philo_count)
{
	int i;

	i = 0;
	while (i < philo_count)
	{
		// if (pthread_mutex_init(&philos[i].forks, NULL))
		// {
		// 	printf("Error: mutex init failed\n");
		// 	return (1);
		// }
		if (pthread_mutex_init(&philos[i].print_mutex, NULL))
		{
			printf("Error: mutex init failed\n");
			return (1);
		}
		if (pthread_mutex_init(&philos[i].meal_check, NULL))
		{
			printf("Error: mutex init failed\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int init_philos(t_data *data)
{
	int i;

	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	if (!data->philos)
	{
		printf("Error: malloc failed\n");
		return (1);
	}
	i = 0;
	while (i < data->philo_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = ft_get_time(data);
		data->philos[i].data = data;
		init_forks(data->philos, data->philo_count);
		if (init_mutex(data->philos, data->philo_count))
			return (1);
		i++;
	}
	return (0);
}

int init_data(t_data *data)
{
//	int i;

	data->one_dead = 0;
	data->all_ate = 0;
	data->start_time = ft_get_time(data);
	if(init_philos(data))
		return (1);
	return (0);
}