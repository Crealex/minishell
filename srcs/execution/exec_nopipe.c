/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_nopipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:58:16 by atomasi           #+#    #+#             */
/*   Updated: 2025/02/24 15:25:55 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int	exec_no_pipe(t_prompt_info *data, int temp_fd[2])
{
	data->str_prt = handle_dollars(data->str_prt, data->env);
	if (!data->str_prt)
		return (0);
	if (!last_step(&data->str_prt , data, temp_fd))
		return (0);
	return (1);
}