#include "philo.h"

unsigned int get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int main(int argc, char **argv)
{	
	//Аргументы
	t_data	data;
	//Check count arguments
	if (argc != 5 && argc != 6)
		return (0);
	//Инициализация аргументов
	init_data(argc, argv, &data);
	create_thread(&data);
	//Wait 5 sec
	sleep(3);
}
