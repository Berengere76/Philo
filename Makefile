
NAME = philo
CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -pthread #-fsanitize=thread

SOURCE =	init.c utils.c utils2.c philo.c monitor.c dinner.c dinner2.c routine.c main.c get_set.c get_set2.c

OBJ 	= $(SOURCE:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

#-g #-fsanitize=thread
