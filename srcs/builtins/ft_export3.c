/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 09:52:45 by atomasi           #+#    #+#             */
/*   Updated: 2025/02/17 10:16:39 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*remove_plus(char *str)
{
	char	*res;
	char	*name;
	char	*content;
	char	*temp;

	name = get_name(str);
	content = get_content(str);
	temp = ft_strjoin(name, "=");
	free(name);
	res = ft_strjoin(temp, content);
	free(temp);
	free(content);
	return (res);
}
