/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:55:00 by alexandre         #+#    #+#             */
/*   Updated: 2025/01/22 16:50:49 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    freesplit(char **str)
{
    int    i;

    i = 0;
    // if (!str || !*str)
    //     return ;
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
int	exist_closing(char *prompt, char c, int i)
{
	static int	in_quote = 0;

	if (in_quote == 1)
	{
		in_quote = 0;
		return (2);
	}
	else if (in_quote == 0)
	{
		while (prompt[i])
		{
			i++;
			if (prompt[i] == c)
			{
				in_quote++;
				return (1);
			}
		}
	}
	return (0);
}

void	update_quote(int *in_single, int *in_double, int *i, char *prompt)
{
	int	quote_status;

	if (prompt[*i] == '\'' && !*in_double)
	{
		quote_status = exist_closing(prompt, '\'', *i);
		if (quote_status == 0)
			return ;
		else if (quote_status == 1)
			*in_single = 1;
		else if (quote_status == 2)
			*in_single = 0;
		(*i)++;
	}
	else if (prompt[*i] == '\"' && !*in_single)
	{
		quote_status = exist_closing(prompt, '\"', *i);
		if (quote_status == 0)
			return ;
		else if (quote_status == 1)
			*in_double = 1;
		else if (quote_status == 2)
			*in_double = 0;
		(*i)++;
	}
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