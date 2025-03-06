/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:42:41 by atomasi           #+#    #+#             */
/*   Updated: 2025/03/06 11:51:55 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static int check_flag(t_prompt_info *data)
// {
// 	int	i;
// 	int	quote[2];

// 	i = 0;
// 	quote[0] = 0;
// 	quote[1] = 0;
// 	while (data->prt_raw[i])
// 	{
// 		while ((data->prt_raw[i] == '\'' && !quote[1]) || (data->prt_raw[i] == '\"' && !quote[0]))
// 			if (!update_quote(&quote[0], &quote[1], &i, data->prt_raw))
// 				break ;
// 		if (data->prt_raw[i] && data->prt_raw[i + 1] &&  data->prt_raw[i] == '-'
// 			&& data->prt_raw[i + 1] == 'n' && !quote[0] && !quote[1])
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

static int	handle_flags(char *prompt, t_prompt_info *data)
{
	int	i;
	int	countn;

	i = 0;
	countn = 0;
	(void)data;
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
		if ((prompt[i] && prompt[i + 1]) && (prompt[i] == ' ' && prompt[i + 1] == ' '))
			return (countn);
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
		n = handle_flags(prompt, data);
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
