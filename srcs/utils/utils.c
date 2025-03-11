/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:24:47 by atomasi           #+#    #+#             */
/*   Updated: 2025/03/11 11:33:17 by dvauthey         ###   ########.fr       */
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

void	freesplit(char **str)
{
	int	i;

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
int	update_exit_code(int param)
{
	static int	code = 0;

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
	len_var = ft_strlen(var);
	while (env[i])
	{
		if (!ft_strncmp(var, env[i], len_var) && env[i][len_var] == '=')
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
	if (data->fd_in)
		free(data->fd_in);
	if (data->fd_out)
		free(data->fd_out);
	if (data->redirection)
		free(data->redirection);
	end_redirect(data, redirect);
}
