/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:37:37 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/20 18:42:01 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// UNIQUEMENT POUR FAIRE DES EXPERIENCES

#include "../includes/minishell.h"

int main()
{
	char *str;

	while (1)
	{
		str = readline("Minishell$> ");
		if (ft_strlen(str) > 0)
			parsing(str);
	}
}