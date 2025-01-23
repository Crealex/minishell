/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:20:22 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/23 10:21:12 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// ATTENTION : SI OPT OU ARG
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
	update_exit_code(0);
}