/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_in_out.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:29:28 by atomasi           #+#    #+#             */
/*   Updated: 2025/03/10 15:29:28 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	in_redirect(char **str)
{
	int	i;
	int	is_double;
	int	quote[2];
	int	len[2];

	init_fd(&i, &quote[0], &quote[1]);
	init_fd(&is_double, &len[0], &len[1]);
	while ((*str)[i])
	{
		update_quote(&quote[0], &quote[1], &i, (*str));
		if (!(*str)[i])
			break ;
		if (!quote[0] && !quote[1] && (*str)[i] == '<')
		{
			len_file(*str, i, &len[0], &len[1]);
			double_quote((*str)[i + 1], '<', &i, &is_double);
			if ((i > 1 && error_out(*str, i))
				|| error(*str, &i, "<", ">"))
			{
				*str = del_rd(*str, len, &i);
				return (0);
			}
			i++;
		}
		i++;
	}
	return (1);
}

int	is_in_rd(char **str, t_prompt_info *data, int index, int *c)
{
	if (!in_redirect(str))
		return (update_exit_code(2), 0);
	data->fd_in[index] = get_in_fd(str, data->fd_in[index], data, *c);
	if (!(*str)[*c])
		(*c)--;
	is_child(0);
	if (data->fd_in[index] == -1)
		return (update_exit_code(1), -1);
	return (update_exit_code(0), 1);
}

static int	out_redirect(char **str)
{
	int	i;
	int	is_double;
	int	quote[2];
	int	len[2];

	init_fd(&i, &quote[0], &quote[1]);
	init_fd(&is_double, &len[0], &len[1]);
	while ((*str)[i])
	{
		update_quote(&quote[0], &quote[1], &i, *str);
		if (!(*str)[i])
			break ;
		if (!quote[0] && !quote[1] && (*str)[i] == '>')
		{
			len_file_out(*str, i, &len[0], &len[1]);
			double_quote((*str)[i + 1], '>', &i, &is_double);
			if (error(*str, &i, ">", "<"))
			{
				*str = del_rd(*str, len, &i);
				return (0);
			}
			i++;
		}
		i++;
	}
	return (1);
}

int	is_out_rd(char **str, t_prompt_info *data, int index, int *c)
{
	if (!out_redirect(str))
		return (update_exit_code(2), 0);
	data->fd_out[index] = get_out_fd(str, data->fd_out[index], data, *c);
	if (!(*str)[*c])
		(*c)--;
	is_child(0);
	if (data->fd_out[index] == -1)
		return (update_exit_code(1), -1);
	return (update_exit_code(0), 1);
}
