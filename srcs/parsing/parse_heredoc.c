/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:46:25 by atomasi           #+#    #+#             */
/*   Updated: 2025/02/13 14:38:21 by atomasi          ###   ########.fr       */
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
	//add_env(data->prompt, int *i, t_str *res, char **all_env)
}