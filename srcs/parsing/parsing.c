/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:30:28 by atomasi           #+#    #+#             */
/*   Updated: 2025/02/20 16:10:31 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>





// static int fork_pipe(char **str, t_prompt_info *data, int len, int (*pipefd)[2])
// {
// 	int		exit_status;
// 	pid_t	pid;
// 	pid_t	pid2;

// 	pipe(pipefd[len - 1]);
// 	pid = fork();
// 		if (pid == 0)
// 	{
// 		if (!last_step(str, data, pipefd))
// 			return (cleanup(data), 0);
// 		else
// 		 	return (2);
// 	}
// 	else if (pid > 0 && len == 1)
// 	{
// 		pid2 = fork();
// 		if (pid2 == 0)
// 		{
// 			data->pos_pipe = 0;
// 			if (!last_step(&data->pipe[0], data, pipefd))
// 				return (cleanup(data), 0);
// 			return (2);
// 		}
// 		is_child(1);
// 		while (data->pipe_len - 1 > 0)
// 		{
// 			waitpid(pid2, NULL, 0);
// 			data->pipe_len--;
// 		}
// 		is_child(0);
// 		update_exit_code(WEXITSTATUS(exit_status));
// 		return (2);
// 	}
// 	else if (pid > 0 && len == 0)
// 	{
// 		printf("in conditon len 0\n");
// 		is_child(1);
// 		waitpid(pid, &exit_status, 0);
// 		is_child(0);
// 		update_exit_code(WEXITSTATUS(exit_status));
// 	}
// 	//waitpid(pid, &exit_status, 0);
// 	return (1);
// }

int parsing(t_prompt_info *data)
{
	int		redirect;
	int		temp_fd[2];

	data->pipe = NULL;
	data->prompt = NULL;
	data->is_pipe = is_pipe(&data->str_prt);
	if (data->is_pipe == -1)
		return (cleanup(data), 1);
	redirect = redirection(data);
	if (redirect == 0)
		return (cleanup(data), 1);
	else if (redirect == 2)
		make_redirect(data, &temp_fd[0], &temp_fd[1]);
	if (data->is_pipe == 1)
	{
		if (!handle_pipe(data) || !exec_pipe(data))
			return (cleanup(data), 1);
	}
	else if (data->is_pipe == 0)
		if (!exec_no_pipe(data))
			return (cleanup(data), 1);
	if (redirect == 2)
		end_redirect(data, temp_fd[0], temp_fd[1]);
	return (cleanup(data), 1);
}
