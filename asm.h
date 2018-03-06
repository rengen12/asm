
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
	int 			op;
	struct s_list   *next;
}					t_list;

typedef struct		s_lab
{
	char			*lab;
	int 			pos;
	int 			indir;
	struct s_lab   *next;
}					t_lab;

size_t	ft_strlen(char *a);
void	ft_bzero(void *b, size_t len);
long		ft_atoi(const char *str);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
t_list	*listadd(t_list *head, t_list *new);
t_list	*listn(char *in);
char	*strjoin(char *a, char *b);
int		get_next_line(const int fd, char **line);
t_list	*lstrev(t_list *com);
int		ft_word_count(char const *s, char c);
int 	ft_strcmp(char *a, char *b);
char	*ft_itoa(int n);
char 	*strconcat(char *a, char *b);
char	**ft_strsplit(char const *s, char c);
t_list	*test_live(char *com, char *in, t_list *error, int num);
char 	*copy_index(char *ret, char *in, int i, int numeric);
t_list	*test_ld(char *com, char *in, t_list *error, int num);
t_list	*test_st(char *in, t_list *error, int num, t_list *code);
t_list	*test_add(char *com, char *in, t_list *error, int num);
t_list	*test_and(char *com, char *in, t_list *error, int num);
t_list	*test_fork(char *com, char *in, int num, t_list *code);
t_list	*test_ldi(char *com, char *in, int num, t_list *code);
t_list	*test_sti(char *com, char *in, int num, t_list *code);
t_list	*test_aff(char *com, char *in, int num);
t_list	*create(t_list *code, t_list *error, char *file);
int		is_label_char(char test);

#endif //COREWAR_ASM_H
