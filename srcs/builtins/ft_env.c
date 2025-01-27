/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:20:22 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/27 16:25:46 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(char **env)
{
	int		i;

	i = 0;
	if (!env || !*env)
	{
		update_exit_code(1);
		return ;
	}
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	int ienv = var_exist("TEST=vsd", env);
	printf("env[ienv] after env :%s\n", env[ienv]);
	update_exit_code(0);
}
