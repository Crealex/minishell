/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:34:55 by dvauthey          #+#    #+#             */
/*   Updated: 2025/03/06 11:38:39 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	result(char **res, char *str, int *index, int is_double)
{
	if (is_double)
		(*index)--;
	(*res)[*index] = ' ';
	(*res)[*index + 1] = str[*index];
	if (is_double)
	{
		(*index)++;
		(*res)[*index + 1] = str[*index];
	}
	(*res)[*index + 2] = ' ';
	*index += 3;
}

char	*add_space(char *str, int i, int is_double)
{
	int		index;
	int		j;
	int		len;
	char	*res;

	index = 0;
	j = 0;
	len = ft_strlen(str);
	res = ft_calloc(len + 3, sizeof(char));
	if (!res)
		return (NULL);
	while (str[j])
	{
		if (index == i)
		{
			result(&res, str, &index, is_double);
			j++;
		}
		if (str[j])
			res[index++] = str[j++];
	}
	res[index] = '\0';
	return (free(str), res);
}
