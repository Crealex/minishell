/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:28:22 by dvauthey          #+#    #+#             */
/*   Updated: 2025/01/17 12:03:36 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_env(char **env, char **prompt, int n)
{
	int	i;
	int	temp;
	int	count;
	int	len_prompt;

	temp = -1;
	count = 0;
	while (prompt[n] && temp != count)
	{
		i = 0;
		temp = count;
		len_prompt = ft_strlen(prompt[n]);
		while (env[i])
		{
			if (!ft_strncmp(env[i], prompt[n], len_prompt))
			{
				count++;
				break;
			}
			i++;
		}
		n++;
	}
	return (count);
}



void	ft_unset(char **env, char **prompt, int n)
{
	int		i;
	int		env_len;
	char	**new_env;

	i = 0;
	while (env[env_len])
		env_len++;
	new_env = ft_calloc(env_len - count_env(env, prompt, n) + 1,
		sizeof(char *));
	

}
