/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:50:04 by dvauthey          #+#    #+#             */
/*   Updated: 2025/03/10 11:45:06 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	clean_close(t_prompt_info *data, int value)
{
	cleanup(data, 1);
	if (data->env)
		freesplit(data->env);
	close(data->fd_history);
	exit(value);
}

void	ft_exit(t_prompt_info *data)
{
	int	i;
	int	value;

	init_two(&i, &value);
	printf("exit\n");
	if (data->prompt[1])
	{
		while ((!i && (data->prompt[1][0] == '+' || data->prompt[1][0] == '-'))
				|| ft_isdigit(data->prompt[1][i]))
			i++;
		if (i != 0 && i == (int)ft_strlen(data->prompt[1]))
			value = ft_atoi(data->prompt[1]);
		else
		{
			print_err("minishell: exit: ", data->prompt[1],
				": numeric argument required\n");
			clean_close(data, 2);
		}
	}
	if (len_double_tab(data->prompt) > 2)
	{
		print_err("minishell: exit: too many arguments\n", NULL, NULL);
		clean_close(data, 1);
	}
	clean_close(data, value);
}
