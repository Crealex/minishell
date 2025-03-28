/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extern.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:08:52 by atomasi           #+#    #+#             */
/*   Updated: 2025/03/19 13:48:24 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_child(int status)
{
	static int	bool = 0;

	if (status == -1)
		return (bool);
	else
		bool = status;
	return (bool);
}

static int	check_acces_file(char *cmd, int i)
{
	char		*file;
	struct stat	statt;

	file = ft_substr(cmd, i, ft_strlen(cmd));
	ft_bzero(&statt, sizeof(statt));
	stat(file, &statt);
	if (S_ISDIR(statt.st_mode) || ft_strlen(file) == 0)
	{
		print_err("minishell: ", cmd, ": Is a directory\n");
		update_exit_code(126);
		return (free(file), 0);
	}
	if (access(file, X_OK) != -1)
		return (free(file), 1);
	if (access(file, F_OK) == -1)
	{
		print_err("minishell: ", cmd, ": No such file or directory\n");
		update_exit_code(127);
		free(file);
		return (0);
	}
	print_err("minishell: ", cmd, ": Permission denied\n");
	update_exit_code(126);
	return (free(file), 0);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*res;
	char	*cmd_path;
	char	**path;

	if (access(cmd, X_OK) != -1 && (cmd[0] == '/' || cmd[0] == '.'))
	{
		if (cmd[0] == '/' && !check_acces_file(cmd, 0))
			return (NULL);
		return (ft_strdup(cmd));
	}
	path = get_all_path(env);
	if (!path)
		return (NULL);
	i = 0;
	cmd_path = ft_strjoin("/", cmd);
	while (path[i])
	{
		res = ft_strjoin(path[i++], cmd_path);
		if (access(res, X_OK) != -1)
			return (freesplit(path), free(cmd_path), res);
		free(res);
	}
	print_err("minishell: ", cmd, ": No such file or directory\n");
	return (freesplit(path), free(cmd_path), update_exit_code(127), NULL);
}

static void	cleanup_exec(t_prompt_info *data)
{
	int	i;

	i = 0;
	if (data->pipe)
		freesplit(data->pipe);
	if (data->str_prt)
		free(data->str_prt);
	while (i < data->pipe_len)
	{
		if (data->fd_in[i] > 2)
			close(data->fd_in[i]);
		if (data->fd_out[i] > 2)
			close(data->fd_out[i]);
		i++;
	}
	if (data->fd_in)
		free(data->fd_in);
	if (data->fd_out)
		free(data->fd_out);
	if (data->redirection)
		free(data->redirection);
	end_redirect(data, 0);
}

int	extern_exec(t_prompt_info *data)
{
	char	*path;
	int		exit_status;
	pid_t	pid;

	if (data->prompt[0] && ((ft_strlen(data->prompt[0]) > 2
				&& data->prompt[0][0] == '.' && data->prompt[0][1] == '/')))
		if (!check_acces_file(data->prompt[0], 2))
			return (0);
	path = get_path(data->prompt[0], data->env);
	if (!path)
		return (0);
	ign_sig();
	pid = fork();
	if (pid == 0)
	{
		reset_sig();
		cleanup_exec(data);
		if (execve(path, data->prompt, data->env) == -1)
			exit (EXIT_FAILURE);
	}
	is_child(1);
	waitpid(pid, &exit_status, 0);
	is_child(0);
	signal_handler();
	return (free(path), update_exit_code(WEXITSTATUS(exit_status)), 1);
}
