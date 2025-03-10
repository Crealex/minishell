/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:46:57 by dvauthey          #+#    #+#             */
/*   Updated: 2025/03/10 11:47:59 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_err(char *s1, char *s2, char *s3)
{
	char	*res;
	char	*temp;

	if (!s2)
	{
		write(2, s1, ft_strlen(s1));
		return ;
	}
	temp = ft_strjoin(s1, s2);
	if (!s3)
	{
		write(2, temp, ft_strlen(temp));
		free(temp);
		return ;
	}
	res = ft_strjoin(temp, s3);
	write(2, res, ft_strlen(res));
	free(temp);
	free(res);
}

int	ft_isspace(int c)
{
	return (c == ' ' || (9 <= c && c <= 13));
}

int	only_space(char **prompt)
{
	int	i;
	int	iprompt;

	i = 0;
	iprompt = 0;
	while (prompt[iprompt])
	{
		while (prompt[iprompt][i])
		{
			if (!ft_isspace(prompt[iprompt][i]))
				return (0);
			i++;
		}
		iprompt++;
	}
	print_err(prompt[0], ": command not found\n", NULL);
	return (update_exit_code(127), 1);
}

char	*char_strjoin(char *str, char c)
{
	int		i;
	char	*result;

	i = 0;
	if (!str)
		result = ft_calloc(2, sizeof(char));
	else
		result = ft_calloc((ft_strlen(str) + 2), sizeof(char));
	if (result == NULL)
		return (NULL);
	while (str && str[i])
	{
		result[i] = str[i];
		i++;
	}
	result[i] = c;
	result[i + 1] = '\0';
	if (str)
		free(str);
	return (result);
}
