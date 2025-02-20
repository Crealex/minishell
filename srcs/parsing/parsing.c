/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:30:28 by atomasi           #+#    #+#             */
/*   Updated: 2025/02/19 17:20:10 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static int	which_builtins(t_prompt_info *data, int (*pipefd)[2])
{
	int fd_in_temp;
	int fd_out_temp;
	//printf("which builtins of : %s\n", data->prompt[0]);
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
		if (extern_exec(data, pipefd) == 0)
			return (0);
	dup_fd_end(data, &fd_in_temp, &fd_out_temp);
	return (1);
}

static int	last_step(char **str, t_prompt_info *data, int (*pipefd)[2])
{
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

static int fork_pipe(char **str, t_prompt_info *data, int len, int (*pipefd)[2])
{
	int		exit_status;
	pid_t	pid;
	pid_t	pid2;

	pipe(pipefd[len - 1]);
	pid = fork();
	if (pid == 0)
	{
		if (!last_step(str, data, pipefd))
			return (cleanup(data), 0);
		else
		 	return (2);
	}
	else if (pid > 0 && len == 1)
	{
		pid2 = fork();
		if (pid2 == 0)
		{
			data->pos_pipe = 0;
			if (!last_step(&data->pipe[0], data, pipefd))
				return (cleanup(data), 0);
			return (2);
		}
		is_child(1);
		waitpid(pid2, &exit_status, 0);

		is_child(0);
		update_exit_code(WEXITSTATUS(exit_status));
		return (2);
	}
	else if (pid > 0 && len == 0)
	{
		is_child(1);
		waitpid(pid, &exit_status, 0);
		is_child(0);
		update_exit_code(WEXITSTATUS(exit_status));
	}
	return (1);
}

int parsing(t_prompt_info *data)
{
	int		(*pipefd)[2];
	int		len;
	int		val_fork;

	data->pipe = NULL;
	data->prompt = NULL;
	pipefd = NULL;
	val_fork = 1;
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
		len = data->pipe_len - 1;
		pipefd = ft_calloc(len, sizeof(int *));
		while (len >= 0)
		{
			data->pos_pipe = len;
			val_fork = fork_pipe(&data->pipe[len], data, len, pipefd);
			if (val_fork == 0)
				return (free(pipefd), cleanup(data), 1);
			else if (val_fork == 2)
				break;
			len--;
		}
		if (pipefd)
			free(pipefd);
		// while (data->pipe_len - 1 >= 0)
		// {
		// 	waitpid(0, NULL, 0);
		// 	data->pipe_len--;
		// }
	}
	else if (data->is_pipe == 0)
	{
		data->str_prt = handle_dollars(data->str_prt, data->env);
		if (check_valid_builtins(data->str_prt) == 0)
		{
			pipefd = ft_calloc(1, sizeof(int *));
			if (fork_pipe(&data->str_prt, data, 0, pipefd) == 0)
				return (free(pipefd), cleanup(data), 1);
			free(pipefd);
		}
		else
		{
			if (!last_step(&data->str_prt , data, NULL))
				return (cleanup(data), 1);
		}

	}
	return (cleanup(data), 1);
}
