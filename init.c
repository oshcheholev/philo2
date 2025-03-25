#include "philo.h"
#include <pthread.h>

int init_forks(t_data *data, t_philo *philo, int philo_count)
{
	// int i;

	// i = 0;
	// while (i < philo_count)
	// {
		// philos[i].first_fork = malloc(sizeof(pthread_mutex_t));
		// philos[i].second_fork = malloc(sizeof(pthread_mutex_t));
		// if (!philos[i].first_fork || !philos[i].second_fork)
		// {
		// 	printf("Error: malloc failed\n");
		// 	return (1);
		// }
		// if (pthread_mutex_init(philos[i].first_fork, NULL))
		// {
		// 	printf("Error: mutex init failed\n");
		// 	return (1);
		// }
		// if (pthread_mutex_init(philos[i].second_fork, NULL))
		// {
		// 	pthread_mutex_destroy(philos[i].first_fork);
		// 	printf("Error: mutex init failed\n");
		// 	return (1);
		// }
		philo->first_fork = &data->forks[philo->id];
		philo->second_fork = &data->forks[(philo->id + 1) % philo_count];
	// 	return (0);
	// 	// philos[i].left_fork = i;
	// 	// philos[i].right_fork = (i + 1) % philo_count;
	// 	i++;
	// }
	return (0);
}

int join_threads(t_data *data)
{
	int i;

	i = 0;
	while (i < data->philo_count)
	{
		printf("joined thread %d\n", i);
		if (pthread_join(data->philos[i].thread, NULL))
		{
			printf("Error: thread join failed\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int create_threads(t_data *data)
{
	t_philo *philo;
	int i;

	i = 0;
	while (i < data->philo_count)
	{
		philo = &data->philos[i];
		printf("creating thread %d\n", i);
		if (pthread_create(&data->philos[i].thread, NULL, &routine, philo))
		{
			printf("Error: thread creation failed\n");
			while(--i >= 0)
			{
				pthread_join(data->philos[i].thread, NULL);
			}
			return (1);
		}
		i++;
	}
	return (0);
}

int init_mutex(t_data *data, t_philo *philos, int philo_count)
{
	int i;

	i = 0;

	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->meal_check, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * philo_count);
	if (!data->forks)
	{
		printf("Error: malloc failed\n");
		return (1);
	}
	while (i < philo_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			printf("Error: mutex init failed for fork %d\n", i);
			return (1);
		}
		i++;
	}
	// i = 0;
	// while (i < philo_count)
	// {
	// 	if (pthread_mutex_init(philos[i].first_fork, NULL))
	// 	{
	// 		printf("Error: mutex init failed\n");
	// 		return (1);
	// 	}
	// 	if (pthread_mutex_init(philos[i].second_fork, NULL))
	// 	{
	// 		pthread_mutex_destroy(philos[i].first_fork);
	// 		printf("Error: mutex init failed\n");
	// 		return (1);
	// 	}
	// 	i++;
	// }
		// if (pthread_mutex_init(&philos[i].print_mutex, NULL))
	// 	{
	// 		printf("Error: mutex init failed\n");
	// 		while (--i >= 0)
	// 		{
	// 			pthread_mutex_destroy(philos[i].first_fork);
	// 			pthread_mutex_destroy(philos[i].second_fork);
	// 		}
	// 			return (1);
	// 	}
	// 	if (pthread_mutex_init(&philos[i].meal_check, NULL))
	// 	{
	// 		printf("Error: mutex init failed\n");
	// 		return (1);
	// 	}
	// 	i++;
	// }
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
		data->philos[i].first_fork = NULL;
		data->philos[i].second_fork = NULL;
		assign_forks(data, data->philos, data->philo_count);
		i++;
	}
	return (0);
}

int init_data(t_data *data)
{
	int i;

	i = 0;
	data->one_dead = 0;
	data->all_ate = 0;
	data->start_time = ft_get_time(data);


	assign_forks(data, &data->philos[i], data->philo_count);
	// data->forks = malloc(sizeof(pthread_mutex_t) * (data->philo_count));
	// if (!data->forks)
	// {
	// 	printf("Error: malloc failed\n");
	// 	return (1);
	// }
	// if(init_philos(data))
	// 	return (1);
	// while(i < data->philo_count)
	// {
	// 	if (init_mutex(data->philos, data->philo_count))
	// 		return (1);
	// 	if (init_forks(data, data->philos, data->philo_count))
	// 		return (1);

	// 	i++;
	// }

	// if (create_threads(data))
	// 	return (1);
	// if (join_threads(data))
	// 	return (1);
	return (0);
}

