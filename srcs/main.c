/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:37:37 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/14 16:41:26 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// UNIQUEMENT POUR FAIRE DES EXPERIENCES

#include "../includes/minishell.h"

int main()
{
	char *str;

	while (1)
	{
		str = readline("Minishell$>");
		parsing(str);
	}
}