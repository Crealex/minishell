/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:55:00 by alexandre         #+#    #+#             */
/*   Updated: 2025/03/06 15:07:13 by dvauthey         ###   ########.fr       */
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
	// if (data->prt_raw)
	// 	free(data->prt_raw);
	while (i < data->pipe_len)
	{
		if (data->fd_in[i] > 2)
			close(data->fd_in[i]);
		if (data->fd_out[i] > 2)
			close(data->fd_out[i]);
		i++;
	}
	if (data->fd_in)
		free(data->fd_in);
	if (data->fd_out)
		free(data->fd_out);
	if (data->redirection)
		free(data->redirection);
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

int	only_space(char **prompt)
{
	int i;
	int iprompt;

	i = 0;
	iprompt = 0;
	while (prompt[iprompt])
	{
		while (prompt[iprompt][i])
		{
			if (!ft_isspace(prompt[iprompt][i]))
				return (0);
			i++;
		}
		iprompt++;
	}
	print_err("minishell: ", prompt[0], ": command not found\n");
	return (update_exit_code(127), 1);
}

char	*char_strjoin(char *str, char c)
{
	int		i;
	char	*result;

	i = 0;
	if (!str)
		result = ft_calloc(2, sizeof(char));
	else
		result = ft_calloc((ft_strlen(str) + 2), sizeof(char));
	if (result == NULL)
		return (NULL);
	while (str && str[i])
	{
		result[i] = str[i];
		i++;
	}
	result[i] = c;
	result[i + 1] = '\0';
	if (str)
		free(str);
	return (result);
}
