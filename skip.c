//
// Created by Denis BUY on 3/7/18.
//

#include "asm.h"

int 	skip_spaces(char *str, int i)
{
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (i);
}

int 	skip_labelchar(char *str, int i)
{
	while (is_label_char(str[i]))
		i++;
	return (i);
}

int 	skip_numeric(char *str, int i)
{
	if (str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	return (i);
}