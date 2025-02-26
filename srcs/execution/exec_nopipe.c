/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_nopipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:58:16 by atomasi           #+#    #+#             */
/*   Updated: 2025/02/26 15:14:37 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int	exec_no_pipe(t_prompt_info *data)
{
	data->str_prt = handle_dollars(data->str_prt, data->env);
	if (!data->str_prt)
		return (0);
	if (!last_step(&data->str_prt , data))
		return (0);
	return (1);
}