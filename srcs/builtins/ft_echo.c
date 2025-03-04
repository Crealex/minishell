/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:42:41 by atomasi           #+#    #+#             */
/*   Updated: 2025/03/04 10:22:17 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static int	end_echo(char *str)
// {
// 	int i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i + 1] && str[i] == 'e' && str[i + 1] == 'c')
// 		{
// 			i += 2;
// 			if (str[i] && str[i + i] && str[i] == 'h' && str[i + 1] == 'o')
// 			{
// 				i += 2;
// 				while (str[i] && str[i] == ' ')
// 					i++;
// 				return (i);
// 			}
// 		}
// 		i++;
// 	}
// 	return (5);
// }

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
