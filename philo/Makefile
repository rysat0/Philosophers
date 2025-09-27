NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror

RM = rm -f

SRCS = chunk_sort1.c chunk_sort2.c main.c order_p.c \
	   order_r.c order_rr.c order_s.c put_error.c \
	   rank.c under_five1.c under_five2.c utils1.c utils2.c \
	   utils3.c


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
