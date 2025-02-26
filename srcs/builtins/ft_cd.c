/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:11:07 by atomasi           #+#    #+#             */
/*   Updated: 2025/02/26 11:36:40 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <string.h>
#include <unistd.h>

static int goto_home(char **env)
{
	char *path;
	char *user;

	user = ft_getenv("USER", env);
	path = ft_strjoin("/home/", user);
	if (!path)
		return (0);
	chdir(path);
	free(path);
	return (1);
}

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
	if (prompt[1] && prompt[2])
	{
		print_err("cd: too many arguments\n", NULL, NULL);
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
	prompt[1] = rm_quote(prompt[1]);
	if (chdir(prompt[1]) == -1 && strncmp(prompt[1], "~", 2) != 0)
	{
		print_err("minishell: cd: ", prompt[1],
			": No such file or directory\n");
	}
	else if (strncmp(prompt[1], "~", 2) == 0)
		goto_home(*env);
	else
		update_env(env);
}
