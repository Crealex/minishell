/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:46:25 by atomasi           #+#    #+#             */
/*   Updated: 2025/02/26 14:47:08 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

char	*parse_heredoc(char *line, t_prompt_info *data)
{
	t_str new_line;
	int il;

	il = 0;
	new_line.i = 0;
	if (data->env == NULL)
		return (line);
	new_line.str = ft_calloc(ft_strlen(line) + 1, sizeof(char));
	while (line[il])
	{
		if (line[il] == '$')
			new_line.str = add_env(line, &il, &new_line, data->env);
		new_line.str[new_line.i] = line[il];
		new_line.i++;
		il++;
	}
	free(line);
	return (new_line.str);
}
