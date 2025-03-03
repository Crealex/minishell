/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:49:50 by atomasi           #+#    #+#             */
/*   Updated: 2025/03/03 16:41:00 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(char **prompt)
{
	char *res;
	// if (prompt[1])
	// {
	// 	ft_putstr_fd("pwd: too many arguments\n", 2);
	// 	update_exit_code(1);
	// 	return ;
	// }
	(void)prompt;
	res = malloc(sizeof(char) * 1000);
	if (!res)
		return ;
	getcwd(res, 1000);
	printf("%s\n", res);
	free(res);
	update_exit_code(0);
}
