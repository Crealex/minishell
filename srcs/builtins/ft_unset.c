/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:28:22 by dvauthey          #+#    #+#             */
/*   Updated: 2025/01/16 11:35:37 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

ft_unset(char **env, char **prompt, int n)
{
	int	i;
	int	in_env;

	i = 0;
	in_env = 1;
	while (prompt[n] && in_env)
	{
		while (env[i])
		{
			if (!ft_strncmp(env[i], prompt[n], ft_strlen(prompt[n])))
			{
				
			}
		}
}
