/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   experience.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:37:37 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/14 14:41:01 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// UNIQUEMENT POUR FAIRE DES EXPERIENCES

#include "../includes/minishell.h"

int main()
{
	char *str;

	str = readline("Minishell$>");
	while (1)
	{
		str = readline("Minishell$>");
		parsing(str);
	}
}