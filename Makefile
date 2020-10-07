CC = gcc
CFLAGS = -c -Wall -Wextra -Werror
LIBS = -Llibft/ -lft
PARSE_DIR =			parse
PARSE_SOURCES =		
MAIN_SOURCES =		main.c parse.c
PARSE_BONUS_SOURCES =	
BONUS_SOURCES =		
NAME = minishell
LIBFT = libft/libft.a
DO_BONUS = 0

ifeq ($(DO_BONUS), 1)
	OBJECTS = $(BONUS_SOURCES:.c=.o)
	HEADERS = minishell_bonus.h
else
	OBJECTS = $(MAIN_SOURCES:.c=.o)
	HEADERS = minishell.h
endif

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT)
	$(CC) -o $(NAME) $(OBJECTS) $(LIBS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

bonus:
	$(MAKE) DO_BONUS=1

$(LIBFT):
	$(MAKE) bonus -C libft/

clean:
	$(MAKE) clean -C libft/
	rm -f parse/*.o
	rm -f *.o

fclean: clean
	$(MAKE) fclean -C libft/
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean bonus re