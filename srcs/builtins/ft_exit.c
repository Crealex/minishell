/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:50:04 by dvauthey          #+#    #+#             */
/*   Updated: 2025/02/14 11:06:42 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_data(t_prompt_info *data)
{
	if (data->str_prt)
		free(data->str_prt);
	if (data->pipe)
		freesplit(data->pipe);
	if (data->prompt)
		freesplit(data->prompt);
	if (data->env)
		freesplit(data->env);
}

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
			write(2, "minishell: exit: ", 17);
			write(2, data->prompt[1], ft_strlen(data->prompt[1]));
			write(2, ": numeric argument required\n", 28);
			value = 2;
		}
	}
	free_data(data);
	printf("exit\n");
	exit(value);
}
