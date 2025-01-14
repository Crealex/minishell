/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:37:37 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/14 17:52:33 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// UNIQUEMENT POUR FAIRE DES EXPERIENCES

#include "../includes/minishell.h"

static void	argv_used(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
}

int main(int argc, char **argv, char **env)
{
	char *str;

	if (argc != 1)
		return (1);
	argv_used(argv);
	while (1)
	{
		str = readline("Minishell$>");
		parsing(str, env);
	}
}