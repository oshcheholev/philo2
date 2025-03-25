
#include "philo.h"

void print_msg(t_data *data, t_philo *philo, char *msg)
{
	long long	time;

	time = ft_get_time(philo->data);
	pthread_mutex_lock(&data->print_mutex);
	printf("%lld %d %s\n", time - philo->data->start_time, philo->id, msg);
	pthread_mutex_unlock(&data->print_mutex);
}

int one_philo(t_data *data, t_philo *philo)
{
	long long	time;

	time = ft_get_time(philo->data);
	pthread_mutex_lock(&data->print_mutex);
	print_msg(data, philo, "has taken a fork");
	pthread_mutex_unlock(&data->print_mutex);
	usleep(data->time_to_die * 1000);
	pthread_mutex_lock(&data->print_mutex);
	print_msg(data, philo, "died");
	pthread_mutex_unlock(&data->print_mutex);

	return (0);
}


int main(int argc, char **argv)
{
	t_data data;

//	data = (t_data)malloc(sizeof(t_data));
	if (argc < 5 || argc > 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	if (parse_args(argc, argv, &data))
		return (1);
	if (init_data(&data))
		return (1);
	if (monitor(&data))
	{
		if(clear_data(&data))
			return (1);
		return (1);
	}
		// if (start_threads(&data))
	// 	return (1);
	// if (wait_threads(&data))
	// 	return (1);
	// if (clear_data(&data))
	// 	return (1);
	return (0);
}