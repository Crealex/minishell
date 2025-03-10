/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:16:41 by marvin            #+#    #+#             */
/*   Updated: 2025/03/10 14:22:09 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

int	len_wquote(char *str)
{
	int	i;
	int	count;
	int	quote[2];

	i = 0;
	count = 0;
	quote[0] = 0;
	quote[1] = 0;
	while (str[i])
	{
		if ((str[i] == '\'' && !quote[1]) || (str[i] == '\"' && !quote[0]))
		{
			if (!update_quote(&quote[0], &quote[1], &i, str))
			{
				i++;
				count++;
			}
		}
		else
		{
			i++;
			count++;
		}
	}
	return (count);
}

char	*rm_cons_quote(char *str)
{
	int		i;
	char	*res;
	int		ires;

	i = 0;
	ires = 0;
	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i + 1] && ((str[i] == '\'' && str[i + 1] == '\'')
				|| (str[i] == '\"' && str[i + 1] == '\"')))
		{
			i += 2;
		}
		if (str[i + 1] && ((str[i] == '\'' && str[i + 1] == '\'')
				|| (str[i] == '\"' && str[i + 1] == '\"')))
			continue ;
		res[ires++] = str[i++];
	}
	res[ires] = '\0';
	return (free(str), res);
}
