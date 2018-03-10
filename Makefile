NAME = asm
NAME2 = dasm

SRC1 = gnl.c main.c support.c list.c split.c itoa.c test1.c create.c skip.c test_header.c
SRC2 = dasm.c support.c list.c itoa.c

OBJ1 = $(SRC1:.c=.o)
OBJ2 = $(SRC2:.c=.o)

HEADER = ./asm.h

all: $(NAME)

%.o: %.c
	gcc -Wall -Wextra -Werror -I $(HEADER) -c $< -o $@

$(NAME): $(OBJ1) $(OBJ2)
	gcc -Wall -Wextra -Werror -o $(NAME) -I $(HEADER) $(SRC1)
	gcc -Wall -Wextra -Werror -o $(NAME2) -I $(HEADER) $(SRC2)

clean:
	rm -f $(OBJ1)
	rm -f $(OBJ2)

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME2)

re: fclean all

.PHONY: clean fclean re all

.NOTPARALLEL: clean fclean re all