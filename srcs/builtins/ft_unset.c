/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:28:22 by dvauthey          #+#    #+#             */
/*   Updated: 2025/01/17 14:50:12 by dvauthey         ###   ########.fr       */
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

static int	is_in_env(char **env, char *prompt)
{
	int	i;
	int	len_prompt;

	i = 0;
	len_prompt = ft_strlen(prompt);
	while (env[i])
	{
		if (!ft_strncmp(env[i], prompt, len_prompt))
			return (0);
		i++;
	}
	return (1);
}

void	ft_unset(char ***env, char **prompt, int n)
{
	int		i;
	int		j;
	int		env_len;
	char	**new_env;

	i = 0;
	j = 0;
	env_len = 0;
	while ((*env)[env_len])
		env_len++;
	new_env = ft_calloc(env_len - count_env(*env, prompt, n) + 1,
		sizeof(char *));
	while (i < env_len)
	{
		if (is_in_env(*env, prompt[n]))
		{
			new_env[j] = *env[i];
			printf("%s\n", new_env[j]);
			j++;
		}
		i++;
	}
	freesplit(*env);
	printf("hi\n");
	env = &new_env;
	printf("bye\n");
}
