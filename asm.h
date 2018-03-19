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
# include <stdio.h>
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
char				*test_and(char *com, char *in, t_list *tmp);
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

#endif
