/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:11:51 by dvauthey          #+#    #+#             */
/*   Updated: 2025/02/26 15:28:24 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	error(char *str, int *i, char *c, char *c1)
{
	(*i)++;
	if (str[*i] && str[*i] == c1[0])
	{
		print_err("minishell: syntax error near unexpected token `", c1, "'\n");
		return (1);
	}
	while (str[*i] && str[*i] == ' ')
		(*i)++;
	if (!str[*i])
	{
		print_err("minishell: syntax error near unexpected token `newline'\n",
			NULL, NULL);
		return (1);
	}
	else if (str[*i] == c[0])
	{
		print_err("minishell: syntax error near unexpected token `", c, "'\n");
		return (1);
	}
	(*i)--;
	while (str[*i] && str[*i] == ' ')
		(*i)--;
	return (0);
}

static void	double_quote(char s, char c, int *i, int *is_double)
{
	if (s && s == c)
	{
		*is_double = 1;
		(*i)++;
	}
}

static int	error_out(char c)
{
	if (c && c == '>')
	{
		print_err("minishell: syntax error near unexpected token `<'\n",
			NULL, NULL);
		return (1);
	}
	return (0);
}

int	in_redirect(char **str)
{
	int	i;
	int	is_double;
	int	quote[2];

	i = 0;
	is_double = 0;
	quote[0] = 0;
	quote[1] = 0;
	while ((*str)[i])
	{
		update_quote(&quote[0], &quote[1], &i, (*str));
		if (!quote[0] && !quote[1] && (*str)[i] == '<')
		{
			double_quote((*str)[i + 1], '<', &i, &is_double);
			if ((i > 0 && error_out(*str[i - 1])) ||
				error(*str, &i, "<", ">"))
				return (0);
			*str = add_space(*str, i, is_double);
			if (!(*str))
				return (0);
			i++;
		}
		i++;
	}
	return (1);
}

int	out_redirect(char **str)
{
	int	i;
	int	is_double;
	int	quote[2];

	i = 0;
	is_double = 0;
	quote[0] = 0;
	quote[1] = 0;
	while ((*str)[i])
	{
		update_quote(&quote[0], &quote[1], &i, *str);
		if (!quote[0] && !quote[1] && (*str)[i] == '>')
		{
			double_quote((*str)[i + 1], '>', &i, &is_double);
			if (error(*str, &i, ">", "<"))
				return (0);
			*str = add_space(*str, i, is_double);
			if (!(*str))
				return (0);
			i++;
		}
		i++;
	}
	return (1);
}
