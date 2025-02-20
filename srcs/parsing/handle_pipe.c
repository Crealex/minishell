/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:08:52 by atomasi           #+#    #+#             */
/*   Updated: 2025/02/20 16:15:10 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_pipe(t_prompt_info *data)
{
	data->pos_pipe = 0;
	data->pipe = ft_splitpipe(data->str_prt, '|');
	if (!data->pipe)
		return (0);
	data->pipe = dollar_pipe(data->pipe, data->env);
	if (!data->pipe)
		return (0);
	data->pipe_len = len_double_tab(data->pipe);
	if (data->pipe_len < 0)
}