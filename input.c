#include "philo.h"

int only_digits(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int ft_atoi(char *str)
{
	int i;
	int res;

	i = 0;
	res = 0;
	while (str[i])
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res);
}

int parce_meals(int argc, char **argv, t_data *data)
{
	if (argc == 6)
	{
		if (!only_digits(argv[5]))
		{
			printf("Error: arguments must be digits\n");
			return (1);
		}
		data->meals_count = ft_atoi(argv[5]);
	}
	else
		data->meals_count = -1;
	return (0);
}

int parse_args(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	if (!only_digits(argv[1]) || !only_digits(argv[2]) || !only_digits(argv[3]) || !only_digits(argv[4]))
	{
		printf("Error: arguments must be digits\n");
		return (1);
	}
	data->philo_count = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (parse_meals(argc, argv, data) == 1)
		return (1);
	return (0);
}
