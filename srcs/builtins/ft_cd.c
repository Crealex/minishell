/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:11:07 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/21 20:11:21 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cd(char **prompt)
{
	char *res;

	if (prompt[1] && prompt[2])
	{
		printf("cd: too many arguments\n");
		update_exit_code(1);
		return ;
	}
	if (!prompt[1])
	{
		chdir("/home");
		update_exit_code(0);
		return ;
	}
	res = malloc(sizeof(char) * 1000);
	if (chdir(prompt[1]) == -1)
		printf("cd: no file or directory name: %s\n", prompt[1]);
	free(res);
}
