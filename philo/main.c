#include "philo.h"

static void	ft_clear(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->message);
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->philo);
	free(data->forks);
}

unsigned int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	create_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
	data->num_philo);
	if (data->forks == NULL)
		return (1);
	while (i < data->num_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (0);
	if (init_data(argc, argv, &data) == 0)
		create_thread(&data);
	ft_clear(&data);
	return (0);
}
