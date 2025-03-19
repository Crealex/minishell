/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:28:11 by atomasi           #+#    #+#             */
/*   Updated: 2025/03/19 10:09:42 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_all_path(char **env)
{
	char	*path_str;
	char	**res;

	path_str = ft_getenv("PATH", env);
	if (!path_str)
		return (NULL);
	res = ft_split(path_str, ':');
	if (!res)
		return (NULL);
	return (res);
}
