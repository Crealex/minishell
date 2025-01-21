/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:37:37 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/21 10:05:13 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// UNIQUEMENT POUR FAIRE DES EXPERIENCES

#include "../includes/minishell.h"

int main()
{
	char *str;

	while (1)
	{
		str = readline("minishell $ > ");
		if (ft_strlen(str) > 0)
			parsing(str);
	}
}