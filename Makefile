NAME = asm

SRC = gnl.c main.c support.c list.c split.c itoa.c test1.c create.c

OBJ = $(SRC:.c=.o)

HEADER = ./asm.h

all: $(NAME)

%.o: %.c
	gcc -Wall -Wextra -Werror -I $(HEADER) -c $< -o $@

$(NAME): $(OBJ)
	gcc -Wall -Wextra -Werror -o $(NAME) -I $(HEADER) $(SRC)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all

.NOTPARALLEL: clean fclean re all