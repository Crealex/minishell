/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:35:36 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/22 17:57:26 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_space_darray(char ***env, int *i)
{
	char **temp;
	int len;

	len = 0;
	while(*env[len])
		len++;
	temp = ft_malloc(sizeof(char *) * (len + 2));
	if (!temp)
		return ;
	while (*env[*i])
	{
		temp[*i] = ft_strdup(*env[*i]);
		(*i)++;
	}
	(*i)++;
	temp[*i] = NULL;
	*i = 0;
	freesplit(*env);
	while (temp[*i])
	{
		*env[*i] = ft_strdup(temp[*i]);
		(*i)++;
	}
	freesplit(temp);
}

void	add_to_env(char *str, char ***env)
{
	char **temp;
	int i;

	i = 0;
	if (check_str(str) == 1) //Gere le = |||| a faire
	{
		add_space_darray(env, &i);
		i--;
		env[i] = ft_strdup(str);
	}
	else if (check_str(str) == 2) // Gere le += |||| a faire
	{
		modify_env(str, env); // a faire
	}
	else
		return ;
}

void	ft_export(char **prompt, char ***env)
{
	int i;

	i = 1;
	if (!prompt[1])
	{
		special_display_env(env); // a faire
		return ;
	}
	(void)env;
	while (prompt[i])
	{
		printf("%s\n", prompt[i]);
		add_to_env(prompt[i], env);
		i++;
	}
}
