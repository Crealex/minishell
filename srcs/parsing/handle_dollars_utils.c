/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollars_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:52:53 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/21 16:01:19 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	len(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

static int	lenp(char *prompt, int i)
{
	int countp;

	countp = 0;
	while (prompt[i])
	{
		countp++;
		i++;
	}
	return (countp);
}

char	*better_strjoin(char const *s1, char const *s2, char *prompt, int ip)
{
	int		i1;
	int		i2;
	char	*result;

	i1 = 0;
	i2 = 0;
	result = malloc((len(s1) + len(s2) + lenp(prompt, ip) + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	while (s1[i1])
	{
		result[i1] = s1[i1];
		i1++;
	}
	while (s2[i2])
	{
		result[i1] = s2[i2];
		i1++;
		i2++;
	}
	result[i1] = '\0';
	return (result);
}
