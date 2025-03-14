/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:02:53 by atomasi           #+#    #+#             */
/*   Updated: 2025/03/14 14:20:32 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

void	make_redirect(t_prompt_info *data)
{
	if (data->fd_in[0] > 2)
		dup2(data->fd_in[0], STDIN_FILENO);
	if (data->fd_out[0] > 2)
		dup2(data->fd_out[0], STDOUT_FILENO);
}

void	end_redirect(t_prompt_info *data, int redirect)
{
	if (redirect)
	{
		dup2(data->temp_fdin, STDIN_FILENO);
		dup2(data->temp_fdout, STDOUT_FILENO);
	}
	close(data->temp_fdin);
	close(data->temp_fdout);
}
