/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:02:04 by dvauthey          #+#    #+#             */
/*   Updated: 2025/01/22 15:30:46 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	freesplit(char **str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*ft_getenv(char *var, char **env)
{
	int	i;
	int	len_var;

	i = 0;
	len_var = strlen(var);
	while (env[i])
	{
		if (!strncmp(var, env[i], len_var) && env[i][len_var] == '=')
			return (env[i] + len_var + 1);
		i++;
	}
	return (NULL);
}

int update_exit_code(int param)
{
    static int code = 0;
    if (param == -1)
        return (code);
    else
        code = param;
    return (code);
}
