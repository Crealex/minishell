/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:03:10 by alexandre         #+#    #+#             */
/*   Updated: 2025/02/06 16:04:16 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_all_path()
{
	char	*path_str;
	char	**res;

	path_str = getenv("PATH");
	if (!path_str)
		return (NULL);
	res = ft_split(path_str, ':');
	if (!res)
		return (NULL);
	return (res);
}