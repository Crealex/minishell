/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:42:41 by atomasi           #+#    #+#             */
/*   Updated: 2025/03/19 11:23:23 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_flags(char *prompt, t_prompt_info *data)
{
	int	i;
	int	countn;

	i = 0;
	countn = 0;
	(void)data;
	while (prompt[i] && (prompt[i] == '-' || ft_isspace(prompt[i])
			|| prompt[i] == 'n'))
	{
		if (prompt[i] == '-')
		{
			if (i > 0 && prompt[i - 1] && !ft_isspace(prompt[i - 1]))
				return (countn);
			i++;
			if (prompt[i] != 'n')
				return (countn);
		}
		i++;
		if (ft_isspace(prompt[i]) || !prompt[i])
			countn = i + 1;
		if ((prompt[i] && prompt[i + 1]) && (ft_isspace(prompt[i])
				&& ft_isspace(prompt[i + 1])))
			return (countn);
	}
	return (countn);
}

void	ft_echo(char *str, t_prompt_info *data, int n)
{
	char	*prompt;
	char	*res;

	if (data->is_pipe == 0)
		prompt = ft_substr(str, 5, ft_strlen(str));
	else
		prompt = ft_substr(data->pipe[data->pos_pipe], 5,
				ft_strlen(data->pipe[data->pos_pipe]));
	if (!prompt)
		return ;
	if (prompt[0] == '-')
	{
		n = handle_flags(prompt, data);
		res = ft_substr(prompt, n, ft_strlen(prompt));
		if (!res)
			return ;
		printf("%s", res);
		free(res);
		if (!n)
			printf("\n");
	}
	else
		printf("%s\n", prompt);
	free(prompt);
	update_exit_code(0);
}
