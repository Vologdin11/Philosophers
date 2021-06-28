#include "philo.h"

static unsigned int get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

static void	print_message(t_philo *philo, char *message)
{
	printf("%u %d %s\n", get_time() - philo->time_start, philo->id, message);
}

static void	check_die(t_data *data)
{
	int	i;

	i = data->num_philo;
	while (i == data->num_philo)
	{
		i = 0;
		while (i < data->num_philo)
		{
			if (get_time() - data->philo[i].time_life >= data->time_die)
				break ;
			i++;
		}
		usleep(1000);
	}
	print_message(&data->philo[i], DIE);
}

static void	*simulation(void *philo)
{
	while (1)
	{
		//Take left fork
		pthread_mutex_lock(((t_philo *)philo)->lfork);
		print_message((t_philo *)philo, FORK);
		//Take right fork
		pthread_mutex_lock(((t_philo *)philo)->rfork);
		print_message((t_philo *)philo, FORK);
		//Philo eat
		((t_philo *)philo)->time_life = get_time();
		print_message((t_philo *)philo, EAT);
		usleep(((t_philo *)philo)->time_eat * 1000);
		//let go forks
		pthread_mutex_unlock(((t_philo *)philo)->rfork);
		pthread_mutex_unlock(((t_philo *)philo)->lfork);
		print_message((t_philo *)philo, SLEEP);
		usleep(((t_philo *)philo)->time_sleep * 1000);
		print_message((t_philo *)philo, THINK);
		usleep(1000);
	}
}

void	create_thread(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_philo)
	{
		data->philo[i].time_life = get_time();
		data->philo[i].time_start = data->philo[i].time_life;
		pthread_create(&data->philo[i].flow, NULL, simulation, (void *)&data->philo[i]);
		i++;
	}
	check_die(data);
}
