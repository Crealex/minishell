/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:37:07 by dvauthey          #+#    #+#             */
/*   Updated: 2025/02/20 15:25:43 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	pipe_handler(t_prompt_info *data, int (*pipefd)[2])
{
	int	i;
	int temp;

	i = data->pos_pipe;
	temp = i;
	if (i < 0)
		return ;
	if (i == 0)
	{
		printf("pipefd[0] in first : %d and pipefd[1] : %d\n", pipefd[i][0], pipefd[i][1]);
		close(pipefd[i][0]);
		dup2(pipefd[i][1], STDOUT_FILENO);
		while (temp < data->pipe_len - 2)
		{
			close(pipefd[temp + 1][1]);
			close(pipefd[temp + 1][0]);
			temp++;
		}
	}
	else if (i == data->pipe_len - 1)
	{
		printf("pipefd[1] in end : %d and piepfd[0] : %d\n", pipefd[i - 1][1], pipefd[i - 1][0]);
		close(pipefd[i - 1][1]);
		dup2(pipefd[i - 1][0], STDIN_FILENO);
   	}
	else
	{
		printf("in middle : pipefd[0]: %d, pipefd[1]: %d\n", pipefd[i - 1][0], pipefd[i][1]);
		close(pipefd[i - 1][1]);
		close(pipefd[i][0]);
		while (temp < data->pipe_len - 2)
		{
			close(pipefd[temp + 1][1]);
			close(pipefd[temp + 1][0]);
			temp++;
		}
		dup2(pipefd[i - 1][0], STDIN_FILENO);
		dup2(pipefd[i][1], STDOUT_FILENO);
	}
}

