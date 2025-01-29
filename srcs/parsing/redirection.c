/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:02:55 by dvauthey          #+#    #+#             */
/*   Updated: 2025/01/29 15:53:23 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	no_redirect(char *str)
{
	int	i;
	int	quote[2];

	i = 0;
	quote[0] = 0;
	quote[1] = 0;
	while (str[i])
	{
		update_quote(&quote[0], &quote[1], &i, str);
		if (!quote[0] && !quote[1] && str[i] == '<')
			return (0);
		if (!quote[0] && !quote[1] && str[i] == '>')
			return (0);
		i++;
	}
	return (1);
}

int	redirection(char *str)
{
	if (no_redirect(str))
		return (0);
	if (!in_redirect(str))
		return (0);
	if (!out_redirect(str))
		return (0);
	return (1);
}