/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:02:55 by dvauthey          #+#    #+#             */
/*   Updated: 2025/01/28 11:51:41 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	no_redirect(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<')
			if (str[i + 1] && str[i + 1] != '<')
				return (1);
		if (str[i] == '>')
			if (str[i + 1] && str[i + 1] != '>')
				return (1);
		i++;
	}
	return (0);
}

static int	in_redirect(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '<')
		return (1);
	while (str[i] == ' ')
		i++;
	if (i != 0 && str[i] == '<')
		return (1);
}

int	redirection(char *str)
{
	int	i;

	i = 0;
	if (!no_redirect(str))
		return (0);
	in_redirect
}