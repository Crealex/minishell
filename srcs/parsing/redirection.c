/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:43:00 by atomasi           #+#    #+#             */
/*   Updated: 2025/03/19 13:43:04 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pre_redirect(t_prompt_info *data, char **str, int index)
{
	data->fd_in[index] = STDIN_FILENO;
	data->fd_out[index] = STDOUT_FILENO;
	if (!space_around(str, '<') || !space_around(str, '>'))
		return (0);
	return (1);
}

int	redirection(t_prompt_info *data, char **str, int index)
{
	int	i;
	int	quote[2];
	int	out;

	init_four(&i, &quote[0], &quote[1], &out);
	while ((*str)[i])
	{
		update_quote(&quote[0], &quote[1], &i, *str);
		if (!(*str)[i])
			break ;
		if (!quote[0] && !quote[1] && (*str)[i] == '<')
		{
			out = is_in_rd(str, data, index, &i);
			if (out == 0 || out == -1)
				return (out);
		}
		if (!quote[0] && !quote[1] && (*str)[i] == '>')
		{
			out = is_out_rd(str, data, index, &i);
			if (out == 0 || out == -1)
				return (out);
		}
		i++;
	}
	return (1);
}
