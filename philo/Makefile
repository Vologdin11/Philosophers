NAME = philo

SRCS = main.c init_data.c create_thread.c

CC = gcc

FLAGS = -Wall -Werror -Wextra

HEADER = philo.h

OBJS = $(SRCS:.c=.o)

%.o : %.c $(HEADER)
		$(CC) $(FLAGS) -c $< -o $@

all : $(NAME)

$(NAME): $(OBJS)
		$(CC) $(FLAGS) -o $(NAME) $(OBJS)

clean :
		rm -rf $(OBJS)

fclean : clean
		rm -rf $(NAME)

re : fclean all