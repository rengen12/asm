/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:30:41 by dbuy              #+#    #+#             */
/*   Updated: 2018/03/14 13:30:43 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

char	*test_skip_reg(char *in, int *i, t_list *tmp)
{
	char	*error;

	if (in[*i] != 'r')
		return (NULL);
	*i = *i + 1;
	if ((error = test_reg(in, *i, tmp->num)) != NULL)
		return (error);
	*i = skip_numeric(in, *i);
	return (NULL);
}

char	*test_sk_label(char *in, int *i, t_list *tmp, t_list *code)
{
	char *error;

	if (in[*i] != LABEL_CHAR)
		return (NULL);
	*i = *i + 1;
	if ((error = test_label(in, *i, tmp, code)) != NULL)
		return (error);
	*i = skip_labelchar(in, *i);
	*i = skip_math(in, *i);
	return (NULL);
}
