//
// Created by Denis BUY on 3/4/18.
//

#include "asm.h"

t_list	*listn(char *in)
{
	t_list *ret;

	ret = (t_list *)malloc(sizeof(t_list));
	ret->next = NULL;
	ret->str = (char*)malloc(ft_strlen(in) + 1);
	ret->str = ft_memmove(ret->str, in, ft_strlen(in) + 1);

	return (ret);
}

t_list	*listadd(t_list *head, t_list *new)
{
	new->next = head;
	return (new);
}

char	*strjoin(char *a, char *b)
{
	size_t	len;
	char	*er;
	int		i;
	int 	j;
	char 	*out;

	printf("GENERING ERROR a = %s\n", a);
	er = "Syntax error at token [";
	len = ft_strlen(er) + ft_strlen(a) + ft_strlen(b) + 2;
	out = (char*)malloc(len + 1);
	out[len] = 0;
	i = -1;
	while (er[++i] != '\0')
		out[i] = er[i];
	j = 0;
	while (a[j] != '\0')
		out[i++] = a[j++];
	out[i] = ':';
	j = 0;
	while (b[j] != '\0')
		out[++i] = b[j++];
	out[++i] = ']';
	printf("ERROR out = %s\n", out);
	return (out);
}

char 	*strconcat(char *a, char *b)
{
	char	*ret;
	int 	i;
	int 	j;

	printf("%s\n", b);
	ret = (char*)malloc(ft_strlen(a) + ft_strlen(b) + 1);
	i = -1;
	while (a[++i] != '\0')
		ret[i] = a[i];
//	i++;
	j = -1;
	while (b[++j] != '\0')
		ret[i++] = b[j];
	ret[i] = '\0';
//	printf("ret = %s\n", ret);
	return (ret);

}

t_list	*lstrev(t_list *com)
{
	t_list *tmp;
	t_list *link;

	if (!com)
		return (NULL);
	tmp = com->next;
	com->next = NULL;
	while (tmp)
	{
		link = tmp->next;
		tmp->next = com;
		com = tmp;
		tmp = link;
	}
	return (com);
}

int 	ft_strcmp(char *a, char *b)
{
	int i;

	i = 0;
	while (a[i] == b[i] && a[i] != '\0' && b[i] != '\0')
		i++;
	return (a[i] - b[i]);

}