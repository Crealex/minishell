/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:21:45 by atomasi           #+#    #+#             */
/*   Updated: 2025/02/03 13:40:50 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_cmd(char **prompt)
{
	int	i;

	if (ft_strncmp("echo", prompt[i], 4) == 0
		|| ft_strncmp("cd", prompt[i], 2) == 0
		|| ft_strncmp("pwd", prompt[i], 3) == 0
		|| ft_strncmp("export", prompt[i], 6) == 0
		|| ft_strncmp("unset", prompt[i], 5) == 0
		|| ft_strncmp("env", prompt[i], 3) == 0
		|| ft_strncmp("exit", prompt[i], 4) == 0)
		return (1);
	else if (access(prompt[i], O_EXCL))
		return (1);
	else return (0);
}
