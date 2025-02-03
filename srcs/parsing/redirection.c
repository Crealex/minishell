/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:02:55 by dvauthey          #+#    #+#             */
/*   Updated: 2025/02/03 14:17:05 by dvauthey         ###   ########.fr       */
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

int	redirection(char **str, t_prompt_info *data)
{
	if (no_redirect(*str))
	{
		data->fd_in = 0;
		data->fd_out = 1;
		return (0);
	}
	if (!in_redirect(str))
		return (-1);
	else
		data->fd_in = -1;
	if (!out_redirect(str))
		return (-1);
	else
		data->fd_out = -1;
	return (1);
}
