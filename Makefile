NAME := philo

CC := cc
RM := rm -f

CFLAGS	= -Wall -Wextra -Werror -pthread #-fsanitize=thread

SOURCE := main.c utils.c init.c dinner.c mtx_handle.c synch_utils.c monitor.c
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

#--tool=helgrind
#--tool=drd