/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:57:04 by atomasi           #+#    #+#             */
/*   Updated: 2025/02/20 16:05:49 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <bits/pthreadtypes.h>
#include <sys/wait.h>
#include <unistd.h>

int	exec_pipe(t_prompt_info  *data)
{
	int	pid;
	int	i;
	int	exit_status;
	int	(*pipefd)[2];

	i = 0;
	while (data->pipe[i])
	{
		if (i < data->pipe_len - 1)
			pipe(pipefd[i]);
		pid = fork();
		if (pid == 0)
		{
			redirect_pipe(data, i);
			if (!last_step(&data->pipe[i], data))
				exit (0);
		}
		waitpid(pid, &exit_status, 0);
		i++;
	}
	update_exit_code(WEXITSTATUS(exit_status));
	return (1);
}