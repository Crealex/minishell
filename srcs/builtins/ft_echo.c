/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:42:41 by atomasi           #+#    #+#             */
/*   Updated: 2025/02/27 17:45:43 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_flags(char *prompt)
{
	int	i;
	int	countn;

	i = 0;
	countn = 0;
	while (prompt[i] && (prompt[i] == '-' || prompt[i] == ' '
			|| prompt[i] == 'n'))
	{
		if (prompt[i] == '-')
		{
			if (i > 0 && prompt[i - 1] && prompt[i - 1] != ' ')
				return (countn);
			i++;
			if (prompt[i] != 'n')
				return (countn);
		}
		i++;
		if (prompt[i] == ' ' || !prompt[i])
			countn = i + 1;
	}
	return (countn);
}

void	ft_echo(char *str, t_prompt_info *data)
{
	char	*prompt;
	char	*res;
	int		n;

	if (data->is_pipe == 0)
		prompt = ft_substr(str, 5, ft_strlen(str));
	else
		prompt = ft_substr(data->pipe[data->pos_pipe], 5,
				ft_strlen(data->pipe[data->pos_pipe]));
	if (!prompt)
		return ;
	if (prompt[0] == '-')
	{
		n = handle_flags(prompt);
		res = ft_substr(prompt, n, ft_strlen(prompt));
		if (!res)
			return ;
		printf("%s", res);
		if (!n)
			printf("\n");
	}
	else
		printf("%s\n", prompt);
	free(prompt);
	update_exit_code(0);
}
