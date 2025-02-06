/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:37:37 by atomasi           #+#    #+#             */
/*   Updated: 2025/02/05 13:36:00 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **env)
{
	int		fd;
	t_prompt_info data;

	if (argc != 1)
		return (1);
	(void)argv;
	data.env = NULL;
	data.env = cpy_double_array(data.env, env);
	if (!data.env)
		return (1);
	fd = open("history", O_CREAT | O_APPEND | O_RDWR,  0744);
	get_history(fd);
	signal_handler();
	while (1)
	{
		data.str_prt = readline("minishell $ > ");
		if (ft_strlen(data.str_prt) > 0)
		{
			manage_history(data.str_prt, fd);
			if (!parsing(&data))
			{
				ft_putstr_fd("Error : Parsing\n", 2);
				if (data.str_prt)
					free(data.str_prt);
				return (-1);
			}
		}
	}
}
