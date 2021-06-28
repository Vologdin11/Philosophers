#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define FORK	"has taken a fork"
# define EAT	"is eating"
# define SLEEP	"is sleeping"
# define THINK	"is thinking"
# define DIE	"died"

typedef struct s_philo
{
	int				id;
	int				time_eat;
	int 			count_eat;
	int				time_sleep;
	unsigned int	time_life;
	unsigned int	time_start;
	pthread_t		flow;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
}				t_philo;

typedef struct s_data
{
	int				num_philo;
	int				time_die;
	int				lasting_eat;
	int				lasting_sleep;
	int				num_each_philo_eat;
	t_philo			*philo;
	pthread_mutex_t	*forks;
}				t_data;

void			init_data(int argc, char **argv, t_data *data);
void			create_thread(t_data *data);

#endif