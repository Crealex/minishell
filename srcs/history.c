/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:46:28 by dvauthey          #+#    #+#             */
/*   Updated: 2025/03/11 09:49:04 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*del_newline(char *str)
{
	int		i;
	char	*new_str;
	int		len_str;

	i = 0;
	len_str = ft_strlen(str);
	new_str = ft_calloc(len_str, sizeof(char));
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\n')
			new_str[i] = '\0';
		else
			new_str[i] = str[i];
		i++;
	}
	free(str);
	return (new_str);
}

void	get_history(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return ;
	line = del_newline(line);
	if (!line)
		return ;
	add_history(line);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (line)
		{
			line = del_newline(line);
			if (!line)
				return ;
			add_history(line);
		}
	}
	if (line)
		free(line);
}

void	manage_history(char *str, int fd)
{
	ft_putstr_fd(str, fd);
	ft_putstr_fd("\n", fd);
	add_history(str);
	close(fd);
}
