/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:37:37 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/24 16:40:23 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **env)
{
	char	**env_cpy;
	char	*str;

	if (argc != 1)
		return (1);
	(void)argv;
	env_cpy = NULL;
	env_cpy = cpy_double_array(env_cpy, env);
	if (!env_cpy)
		return (1);
	while (1)
	{
		str = readline("minishell $ > ");
		if (ft_strlen(str) > 0)
		{
			if (!parsing(str, &env_cpy))
			{
				ft_putstr_fd("Error : Parsing\n", 2);
				if (str)
					free(str);
				return (-1);
			}
		}
	}
}
