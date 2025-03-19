/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:06:39 by dvauthey          #+#    #+#             */
/*   Updated: 2025/03/19 11:39:44 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_endword(char *s1, char *s2, int len)
{
	if (!strncmp(s1, s2, len))
	{
		if (s1[len] == '\n' && !s1[len + 1])
			return (1);
	}
	return (0);
}

static char	*which_heredoc(int *fd, t_prompt_info *data)
{
	static int	old = 2;
	int			current;
	char		*name;

	current = ft_atoi(ft_getenv("SHLVL", data->env));
	name = ft_calloc(3, sizeof(char));
	if (!name)
		return (NULL);
	name[0] = '.';
	name[1] = 'a';
	name[2] = '\0';
	if (current > old)
	{
		*fd = open(name, O_WRONLY);
		while (*fd != -1)
		{
			close(*fd);
			name[1] += 1;
			*fd = open(name, O_WRONLY);
		}
		old = current;
	}
	*fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0744);
	return (name);
}

static int	read_write(int fd, char *end_word, t_prompt_info *data)
{
	char	*line;
	int		len_word;
	char	*name;

	line = get_next_line(0);
	len_word = ft_strlen(end_word);
	if (fd > 2)
		close (fd);
	name = which_heredoc(&fd, data);
	if (fd == -1)
		return (free(name), -1);
	while (line && !is_endword(line, end_word, len_word))
	{
		line = parse_heredoc(line, data);
		write(fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	close(fd);
	fd = open(name, O_RDONLY);
	if (fd == -1)
		return (free(name), -1);
	if (line)
		free(line);
	return (free(name), fd);
}

int	heredoc(char **str, int i, int *fd, t_prompt_info *data)
{
	int		index;
	int		len[2];
	char	*end_word;

	len[0] = i;
	len[1] = 0;
	reset_sig();
	len_file(*str, i, &len[0], &len[1]);
	index = i + 2;
	while (ft_isspace((*str)[index]))
		index++;
	end_word = ft_substr(*str, index, len[1] - index);
	if (!end_word)
		return (-1);
	*fd = read_write(*fd, end_word, data);
	if (*fd == -1)
		return (free(end_word), -1);
	signal_handler();
	*str = del_rd(*str, len, &i);
	if (!(*str))
		return (free(end_word), -1);
	return (free(end_word), *fd);
}
