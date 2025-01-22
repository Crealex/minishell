/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:28:22 by dvauthey          #+#    #+#             */
/*   Updated: 2025/01/22 14:38:06 by dvauthey         ###   ########.fr       */
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
			if (!ft_strncmp(env[i], prompt[n], len_prompt)
				&& env[i][len_prompt] == '=')
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

static int	is_in_env(char *env, char **prompt, int n, int prompt_env)
{
	int	i;
	int	len_prompt;

	i = 0;
	while (i < prompt_env)
	{
		len_prompt = ft_strlen(prompt[n + i]);
		if (!ft_strncmp(env, prompt[n + i], len_prompt)
			&& env[len_prompt] == '=')
			return (0);
		i++;
	}
	return (1);
}

static void	cpy_env(char **new_env, char *env, int *j)
{
	*new_env = env;
	(*j)++;
}

char	**ft_unset(char ***env, char **prompt, int n)
{
	int		index[2];
	int		env_len;
	char	**new_env;
	int		prompt_env;

	index[0] = 0;
	index[1] = 0;
	env_len = 0;
	if (!prompt[n])
		return (update_exit_code(0), *env);
	while ((*env)[env_len])
		env_len++;
	prompt_env = count_env(*env, prompt, n);
	new_env = ft_calloc(env_len - prompt_env + 1, sizeof(char *));
	if (!new_env)
		return (update_exit_code(1), NULL);
	while (index[0] < env_len)
	{
		if (is_in_env((*env)[index[0]], prompt, n, prompt_env))
			cpy_env(&new_env[index[1]], (*env)[index[0]], &index[1]);
		index[0]++;
	}
	new_env[index[1]] = '\0';
	return (update_exit_code(0), free(*env), new_env);
}
