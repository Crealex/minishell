/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:45:59 by dvauthey          #+#    #+#             */
/*   Updated: 2025/01/20 11:51:45 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// ATTENTION : SI OPT OU ARG
void	ft_env(char **env)
{
	int		i;

	i = 0;
	if (!env || !*env)
		return ;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}