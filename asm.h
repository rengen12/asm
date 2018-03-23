/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:40:09 by dbuy              #+#    #+#             */
/*   Updated: 2018/03/14 13:40:11 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_ASM_H
# define COREWAR_ASM_H
# define BUFF_SIZE 32
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct		s_files
{
	int				fd;
	int				active;
	char			*buff;
}					t_files;

typedef struct		s_list
{
	char			*str;
	int				j;
	int				i;
	int				pos;
	int				start;
	int				op;
	int				white;
	int				num;
	struct s_list	*next;
}					t_list;

typedef struct		s_lab
{
	char			*lab;
	int				pos;
	int				math;
	int				start;
	int				indir;
	int				cor;
	struct s_lab	*next;
}					t_lab;

size_t				ft_strlen(char *a);
void				ft_bzero(void *b, size_t len);
long				ft_atoi(const char *str);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
t_list				*listadd(t_list *head, t_list *new);
t_list				*listn(char *in);
char				*strjoin(char *a, char *b);
int					get_next_line(const int fd, char **line);
t_list				*lstrev(t_list *com);
int					ft_strcmp(char *a, char *b);
char				*ft_itoa(int n);
char				*strconcat(char *a, char *b);
char				*copy_index(char *ret, char *in, int i, int numeric);
char				*test_ld(char *com, char *in, t_list *tmp, t_list *code);
char				*test_st(char *in, char *error, t_list *tmp, t_list *code);
char				*test_add(char *com, char *in, t_list *tmp);
char				*test_and(char *com, char *in, t_list *tmp, t_list *code);
char				*test_fork(char *com, char *in, t_list *tmp, t_list *code);
char				*test_ldi(char *com, char *in, t_list *tmp, t_list *code);
char				*test_sti(char *com, char *in, t_list *tmp, t_list *code);
char				*test_aff(char *com, char *in, t_list *tmp);
char				*create(t_list *code, char *file, int display);
int					is_label_char(char test);
int					skip_spaces(char *str, int i);
int					skip_labelchar(char *str, int i);
int					skip_numeric(char *str, int i);
char				*test_header(char *error);
int					is_label_char(char test);
int					skip_math(char *str, int i);
char				*clear_src(t_list *src);
int					skip_com(char *str, char *com);

int					no_file(int display);
int					print_usage(void);
int					print_error(char *error, int display);
char				*make_error(char *error, char *in, int i, t_list *code);
int					print_man(int display);
int					invalid_flags(int display);
int					ft_findstr(char *in, t_list *code);
int					empty(t_list *code);
int					find_comment(char *in);
int					find_s(char *in);
char				*test_code(t_list *code, char *error);
char				*test_str(t_list *tmp, t_list *code);
char				*trim_label(char *in, t_list *tmp);
char				*trim_space(char *in, t_list *tmp);
int					find_op(char *in);
int					is_only_spaces(char *in);
t_list				*src_modif(t_list *src);
char				*test_first(char *in, t_list *code, char *error, \
																char *name);
int					is_substr(char *a, char *b);
int					is_only_spaces(char *in);
char				*copy_index(char *ret, char *in, int i, int numeric);
int					find_op(char *in);

char				*test_first(char *in, t_list *code, char *error, \
																char *name);
char				*test_reg(char *in, int i, int num);
char				*test_label(char *in, int i, t_list *tmp, t_list *code);
char				*test_sk_label(char *in, int *i, t_list *tmp, t_list *code);
char				*test_skip_reg(char *in, int *i, t_list *tmp);
int					init_header(char *header);
int					init_name(char *champ, int pos, t_list *code);
int					init_comment(char *champ, int pos, t_list *code);
int					find_acb(char *in);
int					add_args(char *in, int pos, t_list *tmp, t_lab **add);
t_lab				*save_address(int pos, char *str, t_lab *address,\
																int indir);
int					set_math(t_list *tmp, int i);
int					first_trace(char **champ, int pos, t_list *code, int flag);
void				add_links(char *champ, t_lab *label, t_lab *address);
void				clear_links(t_lab *label, t_lab *address);
int					free_lab_add(t_lab *label, t_lab *address);
int					test_label_repeat(t_lab *label);
t_lab				*add_label(t_lab *head, t_lab *new);
char				*binary(int a);
char				*hexa(unsigned char i);
char				*expand(char **ch, int pos, int max);
t_lab				*new_label(t_list *node, int pos, int i);
void				add_size(char *in, int size);

int					usage(void);
int					dasm_no_file(char *file, int flag);
int					cant_find_file(int flag);
int					wrong_file_name(char *file, int flag);
int					invalid_file(void);
int					add_arg(t_list *out, char *in, int *i, int op);
t_list				*add_command(t_list *out, char *in, int *i, int pos);
t_list				*add_name(t_list *out, char *in, int max, int pos);
t_list				*add_comment(t_list *out, char *in, int max, int pos);
void				set_link(t_list *set, t_list *call);
void				make_link(t_list *code, int i, int val);
char				*ft_strcpy(char *out, char *in);
void				print_list(t_list *code, int flag);
void				clear_list(t_list *in);
void				decompile(char *in, int max, char *file, int flag);
int					find_flag_dasm(int ac, char **av);

#endif
