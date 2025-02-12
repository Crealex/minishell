/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:02:55 by dvauthey          #+#    #+#             */
/*   Updated: 2025/02/12 17:06:27 by dvauthey         ###   ########.fr       */
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

int	redirection(t_prompt_info *data)
{
	data->fd_in = 0;
	data->fd_out = 1;
	if (no_redirect(data->str_prt))
		return (1);
	if (!in_redirect(&(data->str_prt)))
		return (0);
	else
	{
		data->fd_in = get_in_fd(&(data->str_prt), data->fd_in);
		if (data->fd_in == -1)
			return (0);
	}
	if (!out_redirect(&(data->str_prt)))
		return (0);
	else
	{
		data->fd_out = get_out_fd(&(data->str_prt), data->fd_out);
		if (data->fd_out == -1)
			return (0);
	}
	return (1);
}
