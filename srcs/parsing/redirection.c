/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:02:55 by dvauthey          #+#    #+#             */
/*   Updated: 2025/03/10 10:49:01 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	in_redirect(char **str)
{
	int	i;
	int	is_double;
	int	quote[2];

	init_two(&i, &is_double);
	init_two(&quote[0], &quote[1]);
	while ((*str)[i])
	{
		update_quote(&quote[0], &quote[1], &i, (*str));
		if (!quote[0] && !quote[1] && (*str)[i] == '<')
		{
			double_quote((*str)[i + 1], '<', &i, &is_double);
			if ((i > 0 && error_out(*str, i)) ||
				error(*str, &i, "<", ">"))
				return (0);
			i++;
		}
		i++;
	}
	return (1);
}

static int	is_in_rd(char **str, t_prompt_info *data, int index)
{
	if (!in_redirect(str))
		return (update_exit_code(2), 0);
	data->fd_in[index] = get_in_fd(str, data->fd_in[index], data);
	is_child(0);
	if (data->fd_in[index] == -1)
		return (update_exit_code(1), 0);
	return (update_exit_code(0), 1);
}

static int	out_redirect(char **str)
{
	int	i;
	int	is_double;
	int	quote[2];

	init_two(&i, &is_double);
	init_two(&quote[0], &quote[1]);
	while ((*str)[i])
	{
		update_quote(&quote[0], &quote[1], &i, *str);
		if (!quote[0] && !quote[1] && (*str)[i] == '>')
		{
			double_quote((*str)[i + 1], '>', &i, &is_double);
			if (error(*str, &i, ">", "<"))
				return (0);
			i++;
		}
		i++;
	}
	return (1);
}

static int	is_out_rd(char **str, t_prompt_info *data, int index)
{
	if (!out_redirect(str))
		return (update_exit_code(2), 0);
	data->fd_out[index] = get_out_fd(str, data->fd_out[index], data);
	is_child(0);
	if (data->fd_out[index] == -1)
		return (update_exit_code(1), 0);
	return (update_exit_code(0), 1);
}

int	redirection(t_prompt_info *data, char **str, int index)
{
	int	i;
	int	quote[2];

	i = 0;
	quote[0] = 0;
	quote[1] = 0;
	data->fd_in[index] = 0;
	data->fd_out[index] = 1;
	if (!space_around(str, '<'))
		return (0);
	if (!space_around(str, '>'))
		return (0);
	while ((*str)[i])
	{
		update_quote(&quote[0], &quote[1], &i, *str);
		if (!str[i])
			break ;
		if (!quote[0] && !quote[1] && (*str)[i] == '<')
			if (!is_in_rd(str, data, index))
				return (0);
		if (!quote[0] && !quote[1] && (*str)[i] == '>')
			if (!is_out_rd(str, data, index))
				return (0);
		i++;
	}
	return (1);
}
