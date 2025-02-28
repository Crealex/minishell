/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:55:48 by alexandre         #+#    #+#             */
/*   Updated: 2025/02/28 17:20:07 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	no_pipe(char *str)
{
	int	i;
	int	quote[2];

	i = 0;
	quote[0] = 0;
	quote[1] = 0;
	while (str[i])
	{
		update_quote(&quote[0], &quote[1], &i, str);
		if (!quote[0] && !quote[1] && str[i] == '|')
			return (0);
		i++;
	}
	return (1);
}

static int	begin_end_pipe(char *str)
{
	int	len_str;

	len_str = ft_strlen(str);
	if (str[0] == '|' || str[len_str - 1] == '|')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (update_exit_code(2), 1);
	}
	return (0);
}

static int	first_pipe(char *str)
{
	int	i;
	int	inquote[2];
	int	quote_exist;

	i = 0;
	inquote[0] = 0;
	inquote[1] = 0;
	quote_exist = 0;
	if (str[i] == ' ')
	{
		while (str[i] && str[i] == ' ')
		{
			i++;
			update_quote(&inquote[0], &inquote[1], &i, str);
			if (inquote[0] || inquote[1])
				quote_exist = 1;
		}
		if (!inquote[0] && !inquote[1] && str[i] == '|' && !quote_exist)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
			return (update_exit_code(2), 0);
		}
		return (1);
	}
	return (1);
}

static int	verif_empty_pipe(int i, char *str)
{
	int	temp;

	temp = i;
	i++;
	while (str[i] && str[i] == ' ')
		i++;
	if (temp < i && (!str[i] || str[i] == '|'))
	{
		ft_putstr_fd("minishell: syntax error near", 2);
		ft_putstr_fd(" unexpected token `|'\n", 2);
		return (update_exit_code(2), 1);
	}
	return (0);
}

int is_pipe(char **str)
{
	int i;
	int inquote[2];

	i = 0;
	inquote[0] = 0;
	inquote[1] = 0;
	if (no_pipe(*str))
		return (0);
	if (begin_end_pipe(*str) || !first_pipe(*str))
		return (-1);
	while ((*str)[i])
	{
		update_quote(&inquote[0], &inquote[1], &i, *str);
		if (!inquote[0] && !inquote[1] && (*str)[i] == '|')
		{
			if (verif_empty_pipe(i, *str))
				return (-1);
			*str = add_space(*str, i, 0);
			if (!(*str))
				return (-1);
			i++;
		}
		i++;
	}
	return (1);
}
