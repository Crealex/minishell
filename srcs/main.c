/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:37:37 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/23 17:17:31 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// UNIQUEMENT POUR FAIRE DES EXPERIENCES

#include "../includes/minishell.h"

static char	**cpy_env(char **env_cpy, char **env)
{
	int	i;
	int	len_x;

	i = 0;
	len_x = 0;
	while (env[len_x])
		len_x++;
	env_cpy = ft_calloc(len_x + 1, sizeof(char *));
	if (!env_cpy)
		return (NULL);
	while (env[i])
	{
		env_cpy[i] = ft_strdup(env[i]);
		i++;
	}
	env_cpy[i] = '\0';
	return (env_cpy);
}

int main(int argc, char **argv, char **env)
{
	char	**env_cpy;
	char	*str;

	if (argc != 1)
		return (1);
	(void)argv;
	env_cpy = NULL;
	env_cpy = cpy_env(env_cpy, env);
	if (!env_cpy)
		return (1);
	while (1)
	{
		str = readline("minishell $ > ");
		if (ft_strlen(str) > 0)
			parsing(str, &env_cpy);
	}
}