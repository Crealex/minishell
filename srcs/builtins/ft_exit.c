/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:50:04 by dvauthey          #+#    #+#             */
/*   Updated: 2025/01/22 14:15:58 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(char *str_prompt, char *str, char **prompt, char ***env)
{
	int	i;
	int	value;

	i = 0;
	value = 0;
	if (str_prompt)
	{
		while (ft_isdigit(str_prompt[i]))
			i++;
		if (i == (int)ft_strlen(str_prompt))
			value = ft_atoi(str_prompt);
		else
		{
			write(2, "Minishell: exit: ", 17);
			write(2, str_prompt, ft_strlen(str_prompt));
			write(2, ": numeric argument required\n", 28);
			value = 2;
		}
	}
	free(str);
	freesplit(prompt);
	free(*env);
	printf("exit\n");
	exit(value);
}
