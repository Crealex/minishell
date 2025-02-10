/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:55:00 by alexandre         #+#    #+#             */
/*   Updated: 2025/02/10 15:34:29 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**cpy_double_array(char **cpy, char **src)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (src[len])
		len++;
	cpy = ft_calloc(len + 1, sizeof(char *));
	if (!cpy)
		return (NULL);
	while (src[i])
	{
		cpy[i] = ft_strdup(src[i]);
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}

void    freesplit(char **str)
{
    int    i;

    i = 0;
     if (!str || !*str)
         return ;
    while (str[i])
    {
		free(str[i]);
		i++;
	}
	free(str);
}
// -1 = just get de last value
// < -1 = update de exit value
int update_exit_code(int param)
{
	static int code = 0;

	if (param == -1)
		return (code);
	else
		code = param;
	return (code);
}


char	*ft_getenv(char *var, char **env)
{
	int	i;
	int	len_var;

	i = 0;
	len_var = strlen(var);
	while (env[i])
	{
		if (!strncmp(var, env[i], len_var) && env[i][len_var] == '=')
			return (env[i] + len_var + 1);
		i++;
	}
	return (NULL);
}

void	cleanup(t_prompt_info *data)
{
	if (data->prompt)
		freesplit(data->prompt);
	if (data->env)
		freesplit(data->env);
	if (data->pipe)
		freesplit(data->pipe);
	if (data->str_prt)
		free(data->str_prt);
	if (data)
		free(data);
}
/* static char *reverse_split(char **prompt, int i)
{
	char *result;
	char *temp;

	result = malloc(sizeof(char) * (ft_strlen(prompt[i]) + 1));
	if (!result)
		return (NULL);
	if (ft_strlcpy(result, prompt[i], ft_strlen(prompt[i]) + 1) == 0)
		return (NULL);
	i++;
	while (prompt[i])
	{
		temp = ft_strjoin(result, " ");
		if (!temp)
			return (NULL);
		free(result);
		result = ft_strjoin(temp, prompt[i]);
		if (!result)
			return (NULL);
		free(temp);
		i++;
	}
	return (result);
} */