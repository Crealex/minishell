/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:11:07 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/21 16:49:43 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cd(char **prompt)
{
	char *res;

	if (prompt[2])
	{
		perror("too many arguments\n");
		update_exit_code(1);
		return ;
	}
	if (prompt[1])
	{
		chdir("/home");
		update_exit_code(0);
		return ;
	}
	res = malloc(sizeof(char) * 1000);
	chdir(prompt[1]);
	free(res);
}