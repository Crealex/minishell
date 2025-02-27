/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:50:04 by dvauthey          #+#    #+#             */
/*   Updated: 2025/02/27 10:34:46 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(t_prompt_info *data)
{
	int	i;
	int	value;

	i = 0;
	value = 0;
	if (data->prompt[1])
	{
		while (ft_isdigit(data->prompt[1][i]))
			i++;
		if (i == (int)ft_strlen(data->prompt[1]))
			value = ft_atoi(data->prompt[1]);
		else
		{
			print_err("minishell: exit: ", data->prompt[1],
				": numeric argument required\n");
			value = 2;
		}
	}
	cleanup(data, 1);
	if (data->env)
		freesplit(data->env);
	close(data->fd_history);
	printf("exit exit\n");
	exit(value);
}
