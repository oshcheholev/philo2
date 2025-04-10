#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <limits.h>
# include <threads.h>
# include <time.h>

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	int				first_fork;
	int				second_fork;
	long long		last_meal;
	pthread_t		thread;
	struct s_data	*data;
	// int	first_fork;
	// int	second_fork;
	
}					t_philo;

typedef struct s_data
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				one_dead;
	int				all_ate;
	int				meals_count;
	long long		start_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	dead_mutex;
}					t_data;

int init_data(t_data *data);

int monitor(t_data *data);
long long	ft_usleep(long long milliseconds, t_data *data);
int parse_args(int argc, char **argv, t_data *data);

int clear_data(t_data *data);

long long	ft_get_time(t_data *data);

void print_msg(t_data *data, t_philo *philo, char *msg);
int assign_forks(t_data *data, t_philo *philo, int philo_count);
int start_routine(t_data *data, t_philo *philo);
void *routine(void *arg);




#endif

