NAME = asm
NAME2 = dasm

SRC1 = gnl.c main.c support.c list.c itoa.c test1.c test2.c create.c skip.c test_header.c test_sti_aff_fork.c test_st_ld.c test_and_add.c test_ldi.c \
create_head_acb.c add_args.c trace_instr.c create_labels.c hexa_bin_free.c set_math_size.c asm_support.c asm_error.c asm_pr_test.c asm_testcode_teststr.c asm_trim.c asm_test_first.c asm_support2.c
SRC2 = dasm.c support.c list.c itoa.c dasm_errors.c dasm_arg.c dasm_command_comment_name.c dasm_list_link.c dasm_support.c dasm_decompile.c

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