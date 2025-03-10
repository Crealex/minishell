/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:00:16 by atomasi           #+#    #+#             */
/*   Updated: 2025/03/10 15:00:38 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	exist_closing(char *prompt, char c, int i)
{
	static int	in_quote = 0;

	if (in_quote == 1)
	{
		in_quote = 0;
		return (2);
	}
	else if (in_quote == 0)
	{
		if (prompt[i + 1] && prompt[i + 1] == c)
		{
			in_quote = 0;
			return (3);
		}
		while (prompt[i])
		{
			i++;
			if (prompt[i] == c)
			{
				in_quote++;
				return (1);
			}
		}
	}
	return (0);
}

static void	update_status(int quote_status, int *quote)
{
	if (quote_status == 1)
		*quote = 1;
	else if (quote_status == 2)
		*quote = 0;
}

int	update_quote(int *in_single, int *in_double, int *i, char *prompt)
{
	int	quote_status;

	quote_status = 0;
	if (prompt[*i] == '\'' && !*in_double)
	{
		quote_status = exist_closing(prompt, '\'', *i);
		if (quote_status == 0)
			return (0);
		else
			update_status(quote_status, in_single);
		(*i)++;
	}
	else if (prompt[*i] == '\"' && !*in_single)
	{
		quote_status = exist_closing(prompt, '\"', *i);
		if (quote_status == 0)
			return (0);
		else
			update_status(quote_status, in_double);
		(*i)++;
	}
	if (quote_status == 3)
		(*i)++;
	return (1);
}

int	is_quote(char *str)
{
	if (str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')
		return (1);
	if (str[0] == '\"' && str[ft_strlen(str) - 1] == '\"')
		return (1);
	else
		return (0);
}

char	*rm_quote(char *str)
{
	int		i;
	int		ires;
	char	*res;
	int		quote[2];

	i = 0;
	ires = 0;
	quote[0] = 0;
	quote[1] = 0;
	res = ft_calloc((ft_strlen(str) + 1), sizeof(char));
	if (!res)
		return (NULL);
	while ((str)[i])
	{
		if (str[i] && (str[i] == '\'' || str[i] == '\"'))
			update_quote(&quote[0], &quote[1], &i, str);
		if (!(str)[i])
			break ;
		res[ires++] = (str)[i++];
	}
	free(str);
	return (res);
}
