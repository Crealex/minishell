/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:50:04 by dvauthey          #+#    #+#             */
/*   Updated: 2025/02/14 11:22:25 by dvauthey         ###   ########.fr       */
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
			write(2, "minishell: exit: ", 17);
			write(2, data->prompt[1], ft_strlen(data->prompt[1]));
			write(2, ": numeric argument required\n", 28);
			value = 2;
		}
	}
	cleanup(data);
	printf("exit\n");
	exit(value);
}
