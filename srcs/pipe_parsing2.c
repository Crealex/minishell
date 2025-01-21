/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_parsing2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:01:38 by dvauthey          #+#    #+#             */
/*   Updated: 2025/01/21 11:48:32 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	quote_exist(const char *s, int i, char c)
{
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	double_single_quote(const char *s, int i)
{
	if (s[i] == '\"' && quote_exist(s, i + 1, '\"'))
	{
		i++;
		while (s[i] && s[i] != '\"')
			i++;
	}
	else if (s[i] == '\'' && quote_exist(s, i + 1, '\''))
	{
		i++;
		while (s[i] && s[i] != '\'')
			i++;
	}
	if (s[i])
		i++;
	return (i);
}

int	ft_nb_row(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c && s[i] != '\'' && s[i] != '\"')
				i++;
			if (s[i] && s[i] != c)
				i = double_single_quote(s, i);
		}
		while (s[i] && s[i] == c)
			i++;
	}
	return (count);
}
