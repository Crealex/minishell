/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:11:07 by atomasi           #+#    #+#             */
/*   Updated: 2025/02/07 14:43:00 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_env(char ***env)
{
	char *new_pwd;
	char *old_pwd;
	char **new_env;

	new_pwd = NULL;
	new_pwd = getcwd(new_pwd, 1000);
	old_pwd = ft_getenv("PWD", *env);
	new_env = malloc(sizeof(char *) * 4);
	new_env[0] = ft_strdup("Les chat c'est mieux que les chiens");
	new_env[1] = ft_strjoin("PWD=", new_pwd);
	new_env[2] = ft_strjoin("OLDPWD=", old_pwd);
	new_env[3] = NULL;
	ft_export(new_env, env);
	freesplit(new_env);
	free(new_pwd);
}

void	ft_cd(char **prompt, char ***env)
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
		update_env(env);
		update_exit_code(0);
		return ;
	}
	res = malloc(sizeof(char) * 1000);
	if (chdir(prompt[1]) == -1)
		printf("minishell: cd: %s: No such file or directory\n", prompt[1]);
	else
		update_env(env);
	free(res);
}
