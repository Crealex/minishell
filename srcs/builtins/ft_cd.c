/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:11:07 by atomasi           #+#    #+#             */
/*   Updated: 2025/03/12 11:32:14 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void	update_env(char ***env)
{
	char	*new_pwd;
	char	*old_pwd;
	char	**new_env;

	new_pwd = NULL;
	new_pwd = malloc(sizeof(char) * 1000);
	if (!new_pwd)
		return ;
	new_pwd = getcwd(new_pwd, 1000);
	old_pwd = ft_getenv("PWD", *env);
	new_env = malloc(sizeof(char *) * 4);
	if (!new_env)
		return ;
	new_env[0] = ft_strdup("Les chat c'est mieux que les chiens");
	new_env[1] = ft_strjoin("PWD=", new_pwd);
	new_env[2] = ft_strjoin("OLDPWD=", old_pwd);
	new_env[3] = NULL;
	ft_export(new_env, env);
	freesplit(new_env);
	free(new_pwd);
}

static int	goto_last_path(char ***env)
{
	char	*path;

	path = ft_getenv("OLDPWD", *env);
	if (!path)
		return (0);
	chdir(path);
	path = malloc(sizeof(char) * 1000);
	getcwd(path, 1000);
	printf("%s\n", path);
	free(path);
	update_env(env);
	return (1);
}

static int	goto_home(char ***env)
{
	char	*path;
	char	*user;

	user = ft_getenv("USER", *env);
	path = ft_strjoin("/home/", user);
	if (!path)
		return (0);
	chdir(path);
	free(path);
	return (1);
}

static void	handle_err(char *str)
{
	struct stat	statt;

	statt.st_mode = 0;
	stat(str, &statt);
	if (!S_ISDIR(statt.st_mode) && access(str, F_OK) != -1)
	{
		print_err("cd: ", str, ": Not a directory\n");
	}
	else
	{
		print_err("minishell: cd: ", str,
			": No such file or directory\n");
	}
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
		goto_home(env);
		update_env(env);
		update_exit_code(0);
		return ;
	}
	if (strncmp(prompt[1], "~", 2) == 0)
		goto_home(env);
	else if (strncmp(prompt[1], "-", 2) == 0)
		goto_last_path(env);
	else if (chdir(prompt[1]) == -1)
	{
		handle_err(prompt[1]);
		update_exit_code(1);
	}
	else
		update_env(env);
}
