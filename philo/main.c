#include "philo.h"

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
}
