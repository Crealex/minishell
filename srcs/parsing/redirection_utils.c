/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:11:51 by dvauthey          #+#    #+#             */
/*   Updated: 2025/03/10 15:31:23 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	error(char *str, int *i, char *c, char *c1)
{
	int	temp;

	temp = *i;
	(*i)++;
	while (str[*i] && isspace(str[*i]))
		(*i)++;
	if (str[*i] && str[*i] == c1[0])
		return (print_err("minishell: syntax error near unexpected token `",
				c1, "'\n"), update_exit_code(2), 1);
	if (!str[*i])
	{
		print_err("minishell: syntax error near unexpected token `newline'\n",
			NULL, NULL);
		return (update_exit_code(2), 1);
	}
	else if (temp < *i && (str[*i] == c[0] || str[*i] == c1[0]))
	{
		print_err("minishell: syntax error near unexpected token `", c, "'\n");
		return (update_exit_code(2), 1);
	}
	(*i)--;
	while (str[*i] && isspace(str[*i]))
		(*i)--;
	return (0);
}

void	double_quote(char s, char c, int *i, int *is_double)
{
	if (s && s == c)
	{
		*is_double = 1;
		(*i)++;
	}
	else
		*is_double = 0;
}

int	error_out(char *str, int i)
{
	i--;
	while (i >= 0 && isspace(str[i]))
		i--;
	if (str[i] == '>')
	{
		print_err("minishell: syntax error near unexpected token `<'\n",
			NULL, NULL);
		update_exit_code(2);
		return (1);
	}
	return (0);
}

int	space_around(char **str, char c)
{
	int	i;
	int	is_double;
	int	quote[2];

	init_two(&i, &is_double);
	init_two(&quote[0], &quote[1]);
	while ((*str)[i])
	{
		update_quote(&quote[0], &quote[1], &i, *str);
		if (!quote[0] && !quote[1] && (*str)[i] == c)
		{
			double_quote((*str)[i + 1], c, &i, &is_double);
			*str = add_space(*str, i, is_double);
			if (!(*str))
				return (0);
			if (is_double)
				i++;
			i++;
		}
		i++;
	}
	return (1);
}
