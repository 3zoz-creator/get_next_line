NAME = GNL.a
CC = cc 
CFLAGS = -Wall -Wextra -Werror

SRCS = get_next_line_utils.c get_next_line.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c get_next_line.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re