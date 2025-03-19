/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_wquote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:26:56 by atomasi           #+#    #+#             */
/*   Updated: 2025/03/19 10:38:38 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_nb_row_wspace(char const *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (!ft_isspace(s[i]))
		{
			count++;
			while (s[i] && !ft_isspace(s[i]) && s[i] != '\'' && s[i] != '\"')
				i++;
			if (s[i] && !ft_isspace(s[i]))
				i = double_single_quote(s, i);
		}
		while (s[i] && ft_isspace(s[i]))
			i++;
	}
	return (count);
}

static int	ft_nb(const char *s, int i, int *start)
{
	while (s[i] && ft_isspace(s[i]))
		i++;
	*start = i;
	while (s[i] && !ft_isspace(s[i]) && s[i] != '\'' && s[i] != '\"')
	{
		i++;
	}
	if (s[i] && !ft_isspace(s[i]))
		i = double_single_quote(s, i);
	while (s[i] && !ft_isspace(s[i]))
		i++;
	return (i);
}

static char	*ft_strinrow(char const *s, int start, int end)
{
	char	*row;
	int		i;

	i = 0;
	row = malloc((end - start + 1) * sizeof(char));
	if (row == NULL)
		return (NULL);
	while (i < (end - start))
	{
		row[i] = s[start + i];
		i++;
	}
	row[i] = '\0';
	return (row);
}

char	**split_wquote(char const *s)
{
	int		index[2];
	int		start;
	char	**result;

	index[0] = 0;
	index[1] = 0;
	start = 0;
	result = malloc((ft_nb_row_wspace(s) + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	while (s[index[0]])
	{
		index[0] = ft_nb(s, index[0], &start);
		if (start != index[0])
		{
			result[index[1]] = ft_strinrow(s, start, index[0]);
			if (!result[index[1]])
				return (ft_freesplit(result, index[1]));
			index[1]++;
		}
		else
			break ;
	}
	result[index[1]] = NULL;
	return (result);
}
