#include "philo.h"

long long	ft_get_time(t_data *data)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
//	ft_get_time(&time, data);
	// printf("time.tv_sec = %ld\n", time.tv_sec);
	// printf("time.tv_usec = %ld\n", time.tv_usec);
	// printf("data->start = %lld\n", data->start);
	return ((((long long)time.tv_sec * 1000) + \
	((long long)time.tv_usec / 1000)) - (long long)data->start_time);
}

long long	ft_usleep(long long milliseconds, t_data *data)
{
	int	start;

	start = ft_get_time(data);
	while (ft_get_time(data) - start < milliseconds)
		usleep(100);
	return (0);
}