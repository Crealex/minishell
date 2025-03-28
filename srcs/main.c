/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:37:37 by atomasi           #+#    #+#             */
/*   Updated: 2025/03/18 16:47:33 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	prompt_handler(t_prompt_info *data)
{
	manage_history(data, data->str_prt);
	if (!parsing(data))
	{
		ft_putstr_fd("Error : ton papa le gentil shrek\n", 2);
		return (0);
	}
	return (1);
}

void	update_shell_level(t_prompt_info *data)
{
	int		lvl;
	char	*new_lvl;
	char	**false_prompt;

	lvl = ft_atoi(ft_getenv("SHLVL", data->env));
	if (lvl == 0)
		lvl = 2;
	new_lvl = ft_itoa(lvl + 1);
	false_prompt = malloc(sizeof(char *) * 3);
	false_prompt[0] = ft_strdup("Une testicule de grenouille");
	false_prompt[1] = ft_strjoin("SHLVL=", new_lvl);
	false_prompt[2] = NULL;
	ft_export(false_prompt, &data->env);
	freesplit(false_prompt);
	free(new_lvl);
}

static int	str_empty(t_prompt_info *data)
{
	if (!data->str_prt)
	{
		if (data->env)
			freesplit(data->env);
		if (data->fd_history > 2)
			close(data->fd_history);
		printf("exit\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_prompt_info	data;

	if (argc != 1)
		return (1);
	(void)argv;
	data.str_prt = NULL;
	data.env = NULL;
	data.env = cpy_double_array(data.env, env);
	data.fd_history = open(".history", O_CREAT | O_APPEND | O_RDWR, 0744);
	get_history(data.fd_history);
	signal_handler();
	update_shell_level(&data);
	while (1)
	{
		data.str_prt = readline("minishell $ > ");
		if (str_empty(&data))
			return (update_exit_code(-1));
		if (ft_strlen(data.str_prt) > 0)
		{
			if (!prompt_handler(&data))
				return (1);
		}
	}
	return (update_exit_code(-1));
}
