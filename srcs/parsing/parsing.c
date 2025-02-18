/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:30:28 by atomasi           #+#    #+#             */
/*   Updated: 2025/02/18 17:25:40 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <fcntl.h>
#include <unistd.h>

static int	which_builtins(t_prompt_info *data, int pipefd[2])
{
	int fd_in_temp;
	int fd_out_temp;

	dup_fd_start(data, &fd_in_temp, &fd_out_temp, pipefd);
	if (!ft_strncmp(data->prompt[0], "echo", 4))
		ft_echo(data->str_prt);
	else if (!ft_strncmp(data->prompt[0], "cd", 2))
		ft_cd(data->prompt, &data->env);
	else if (!ft_strncmp(data->prompt[0], "pwd", 3))
		ft_pwd(data->prompt);
	else if (!ft_strncmp(data->prompt[0], "export", 6))
		ft_export(data->prompt, &data->env);
	else if (!ft_strncmp(data->prompt[0], "unset", 5))
		data->env = ft_unset(&data->env, data->prompt, 1);
	else if (!ft_strncmp(data->prompt[0], "env", 3))
		ft_env(data->env);
	else if (!ft_strncmp(data->prompt[0], "exit", 4))
		ft_exit(data);
	else
		if (extern_exec(data) == 0)
			return (0);
	dup_fd_end(data, &fd_in_temp, &fd_out_temp);
	return (1);
}

static int	last_step(char **str, t_prompt_info *data, int pipefd[2])
{
	printf("dans le fork\n");
	if (only_space(*str))
		return (1);
	data->prompt = split_wquote(*str, ' ');
	if (!data->prompt)
		return (0);
	*str = rm_quote(*str);
	if (!(*str))
		return (0);
	if (!is_valid_cmd(*str))
		return (1);
	if (!check_builtins(data->prompt))
		return (1);
	else
 		if (which_builtins(data, pipefd) == 0)
			return (0);
	return (1);
}

static int fork_pipe(char **str, t_prompt_info *data)
{
	int		pipefd[2];
	pid_t	pid;

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		if (!last_step(str, data, pipefd))
			return (cleanup(data), 1);
	}
	return (1);
}

int parsing(t_prompt_info *data)
{
	// int		ip;
	int		len;

	// ip = 0; 
	data->pipe = NULL;
	// data->pipefd = NULL;
	data->is_pipe = is_pipe(&data->str_prt);
	if (data->is_pipe == -1)
		return (cleanup(data), 1);
	if (!redirection(data))
		return (cleanup(data), 1);
	if (data->is_pipe == 1)
	{
		data->pipe = ft_splitpipe(data->str_prt, '|');
		if (!data->pipe)
			return (cleanup(data), 1);
		data->pipe = dollar_pipe(data->pipe, data->env);
		if (!data->pipe)
			return (cleanup(data), 1);
		data->pipe_len = len_double_tab(data->pipe);
		// data->pipefd = ft_calloc(data->pipe_len - 1, sizeof(int *));
		// if (!data->pipefd)
		// 	return (cleanup(data), 1);
		// while (ip < data->pipe_len - 1)
		// {
		// 	if (ip != data->pipe_len && pipe(data->pipefd[ip]) == -1)
		// 		return (cleanup(data), 1);
		// 	printf("pipe : %i, %i\n", data->pipefd[ip][0], data->pipefd[ip][1]);
		// 	ip++;
		// }
		len = data->pipe_len - 1;
		while (len >= 0)
		{
			data->pos_pipe = len;
			printf("hiiiiii\n");
			if (fork_pipe(&data->pipe[len], data))
				return (cleanup(data), 1);
			len--;
		}
	}
	else if (data->is_pipe == 0)
	{
		data->str_prt = handle_dollars(data->str_prt, data->env);
		if (!last_step(&data->str_prt , data, NULL))
			return (cleanup(data), 1);
	}
	return (cleanup(data), 1);
}
