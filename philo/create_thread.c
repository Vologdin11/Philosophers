#include "philo.h"

static void	*simulation(void *philo)
{
	while (1)
	{
		//Take left fork
		pthread_mutex_lock(((t_philo *)philo)->lfork);
		printf("Take lfork %d\n", ((t_philo *)philo)->id);
		//Take right fork
		pthread_mutex_lock(((t_philo *)philo)->rfork);
		printf("Take rfork %d\n", ((t_philo *)philo)->id);
		//Philo eat
		printf("Eat %d\n", ((t_philo *)philo)->id);
		((t_philo *)philo)->time_life = get_time();
		usleep(((t_philo *)philo)->time_eat * 1000);
		//let go forks
		pthread_mutex_unlock(((t_philo *)philo)->rfork);
		pthread_mutex_unlock(((t_philo *)philo)->lfork);
		printf("Sleep %d\n", ((t_philo *)philo)->id);
		usleep(((t_philo *)philo)->time_sleep * 1000);
		printf("Think %d\n", ((t_philo *)philo)->id);
	}
}

void	create_thread(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_create(&data->philo[i].flow, NULL, simulation, (void *)&data->philo[i]);
		i++;
	}
}
