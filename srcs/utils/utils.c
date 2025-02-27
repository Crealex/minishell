/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:55:00 by alexandre         #+#    #+#             */
/*   Updated: 2025/02/28 15:21:54 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**cpy_double_array(char **cpy, char **src)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (!src || !*src)
		return (NULL);
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
	if (!env || !*env)
		return (NULL);
	len_var = strlen(var);
	while (env[i])
	{
		if (!strncmp(var, env[i], len_var) && env[i][len_var] == '=')
			return (env[i] + len_var + 1);
		i++;
	}
	return (NULL);
}

void	cleanup(t_prompt_info *data, int redirect)
{
	int	i;

	i = 0;
	if (data->prompt)
		freesplit(data->prompt);
	if (data->pipe)
		freesplit(data->pipe);
	if (data->str_prt)
		free(data->str_prt);
	while (i < data->pipe_len)
	{
		if (data->fd_in[i] > 2)
			close(data->fd_in[i]);
		if (data->fd_out[i] > 2)
			close(data->fd_out[i]);
		i++;
	}
	// if (data->fd_in)
	// 	free(data->fd_in);
	// if (data->fd_out)
	// 	free(data->fd_out);
	end_redirect(data, redirect);
}

void	print_err(char *s1, char *s2, char *s3)
{
	char *res;
	char *temp;

	if (!s2)
	{
		ft_putstr_fd(s1, 2);
		return ;
	}
	temp = ft_strjoin(s1, s2);
	if (!s3)
	{
		ft_putstr_fd(temp, 2);
		free(temp);
		return ;
	}
	res = ft_strjoin(temp, s3);
	ft_putstr_fd(res, 2);
	free(temp);
	free(res);
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

int	ft_isspace(int c)
{
	return (c == ' ' || (9 <= c && c <= 13));
}

int	only_space(char *str)
{
	int i;

	i = 0;
	if (!str)
	{
		print_err("minishell: : command not found\n", NULL, NULL);
		return (1);
	}
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	print_err("minishell: ", str, ": command not found\n");
	return (1);
}
