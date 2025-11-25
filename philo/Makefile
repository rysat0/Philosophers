NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

RM = rm -f

SRCS = init.c main.c monitor.c routine.c thread.c utils.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	cc -o $(NAME) $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all
