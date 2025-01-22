/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:42:07 by dvauthey          #+#    #+#             */
/*   Updated: 2025/01/22 11:58:04 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	no_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			return (0);
		i++;
	}
	return (1);
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
			return (0);
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
		return (0);
	}
	return (1);
}

int is_pipe(char *str)
{
    int i;
    int inquote[2];

    i = 0;
    inquote[0] = 0;
    inquote[1] = 0;
	if (no_pipe(str))
		return (0);
	if (!first_pipe(str))
		return (0);
    while (str[i])
    {
		update_quote(&inquote[0], &inquote[1], &i, str);
		if (!inquote[0] && !inquote[1] && str[i] == '|' )
		{
			if (!verif_empty_pipe(i, str))
				return (0);
		}
		i++;
    }
    return (1);
}
