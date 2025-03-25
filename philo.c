
#include "philo.h"

int main(int argc, char **argv)
{
	t_data data;

	if (parse_args(argc, argv, &data))
		return (1);
	if (init_data(&data))
		return (1);
	// if (start_threads(&data))
	// 	return (1);
	// if (wait_threads(&data))
	// 	return (1);
	if (clear_data(&data))
		return (1);
	return (0);
}