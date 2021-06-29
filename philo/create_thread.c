#include "philo.h"

static unsigned int get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

static void	print_message(t_philo *philo, char *message)
{
	pthread_mutex_lock(((t_philo *)philo)->message);
	printf("%u %d %s\n", get_time() - philo->time_start, philo->id, message);
	pthread_mutex_unlock(((t_philo *)philo)->message);
}

static void	check_die(t_data *data)
{
	int	i;

	i = data->num_philo;
	while (i == data->num_philo)
	{
		i = 0;
		data->count_eating_philo = 0;
		while (i < data->num_philo)
		{
			if (get_time() - data->philo[i].time_life >= (unsigned int)data->time_die)
				break ;
			if (data->num_each_philo_eat > 0 && data->philo[i].count_eat >= data->num_each_philo_eat)
				data->count_eating_philo++;
			i++;
		}
		if (data->num_each_philo_eat > 0 && data->count_eating_philo == data->num_philo)
			return ;
	}
	print_message(&data->philo[i], DIE);
}

static void ft_sleep(unsigned int time_sleep)
{
	unsigned int	time_stop;
	unsigned int 	time_start;

	time_stop = get_time() + time_sleep;
	time_start = get_time();
	while (time_start < time_stop)
	{
		usleep(50);
		time_start = get_time();
	}
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
		((t_philo *)philo)->count_eat++;
		print_message((t_philo *)philo, EAT);
		ft_sleep(((t_philo *)philo)->time_eat);
		//let go forks
		pthread_mutex_unlock(((t_philo *)philo)->lfork);
		usleep(100);
		pthread_mutex_unlock(((t_philo *)philo)->rfork);
		print_message((t_philo *)philo, SLEEP);
		ft_sleep(((t_philo *)philo)->time_sleep);
		print_message((t_philo *)philo, THINK);
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
		usleep(100);
	}
	check_die(data);
}
