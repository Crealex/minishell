/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:28:11 by atomasi           #+#    #+#             */
/*   Updated: 2025/03/10 15:28:14 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_all_path(void)
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
