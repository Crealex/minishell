/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:02:55 by dvauthey          #+#    #+#             */
/*   Updated: 2025/02/26 15:23:29 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	no_redirect(char *str)
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
			return (0);
		if (!quote[0] && !quote[1] && str[i] == '>')
			return (0);
		i++;
	}
	return (1);
}

int	redirection(t_prompt_info *data, char **str, int i)
{
	data->fd_in[i] = 0;
	data->fd_out[i] = 1;
	if (no_redirect(*str))
		return (1);
	if (!in_redirect(str))
		return (0);
	else
	{
		data->fd_in[i] = get_in_fd(str, data->fd_in[i], data);
		is_child(0);
		if (data->fd_in[i] == -1)
			return (0);
	}
	if (!out_redirect(str))
		return (0);
	else
	{
		data->fd_out[i] = get_out_fd(str, data->fd_out[i]);
		if (data->fd_out[i] == -1)
			return (0);
	}
	return (2);
}
