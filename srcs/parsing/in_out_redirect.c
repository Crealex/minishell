/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:11:51 by dvauthey          #+#    #+#             */
/*   Updated: 2025/01/29 14:56:50 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	error(char *str, int *i, char *c)
{
	(*i)++;
	while (str[*i] && str[*i] == ' ')
		(*i)++;
	if (!str[*i])
	{
		ft_putstr_fd("minishell: syntax error ", 2);
		ft_putstr_fd("near unexpected token `newline'\n", 2);
		return (1);
	}
	else if (str[*i] == c[0])
	{
		ft_putstr_fd("minishell: syntax error ", 2);
		ft_putstr_fd("near unexpected token `", 2);
		ft_putstr_fd(c, 2);
		ft_putstr_fd("'\n", 2);
		return (1);
	}
	return (0);
}

int	in_redirect(char *str)
{
	int	i;
	int	quote[2];

	i = 0;
	quote[0] = 0;
	quote[1] = 0;
	while (str[i])
	{
		update_quote(&quote[0], &quote[1], &i, str);
		if (!quote[0] && !quote[1] && str[i] == '<')
		{
			if (error(str, &i, "<"))
				return (0);
		}
		i++;
	}
	return (1);
}

int	out_redirect(char *str)
{
	int	i;
	int	quote[2];

	i = 0;
	quote[0] = 0;
	quote[1] = 0;
	while (str[i])
	{
		update_quote(&quote[0], &quote[1], &i, str);
		if (!quote[0] && !quote[1] && str[i] == '>')
		{
			if (str[i + 1] && str[i + 1] == '<')
			{
				ft_putstr_fd("minishell: syntax error", 2);
				ft_putstr_fd(" near unexpected token `<'\n", 2);
				return (0);
			}
			if (error(str, &i, ">"))
				return (0);
		}
		i++;
	}
	return (1);
}
