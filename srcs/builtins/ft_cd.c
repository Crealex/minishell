/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:11:07 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/29 17:39:35 by atomasi          ###   ########.fr       */
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
	//	modify $PDW and $OLDPWD
	//	OLDPWD = PDW
	//	PDW = get_cwd
	free(res);
}
