/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 09:52:45 by atomasi           #+#    #+#             */
/*   Updated: 2025/03/10 10:43:26 by atomasi          ###   ########.fr       */
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

int	len_double_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab || !*tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

int	longer_str(char **tab)
{
	int	longer;
	int	i;
	int	actual_len;

	i = 0;
	longer = 0;
	actual_len = 0;
	while (tab[i])
	{
		actual_len = ft_strlen(tab[i]);
		if (actual_len > longer)
			longer = actual_len;
		i++;
	}
	return (longer);
}
