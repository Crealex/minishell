/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:06:39 by dvauthey          #+#    #+#             */
/*   Updated: 2025/02/14 10:56:40 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	read_write(int fd, char *end_word, t_prompt_info *data)
{
	char	*line;
	int		len_word;
	(void)data;

	line = get_next_line(1);
	len_word = ft_strlen(end_word);
	if (fd > 2)
		close (fd);
	fd = open("heredoc", O_RDWR | O_CREAT | O_TRUNC, 0744);
	if (fd == -1)
		return (-1);
	while (ft_strncmp(line, end_word, len_word) != 0)
	{
		line = parse_heredoc(line, data);
		write(fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(1);
	}
	if (line)
		free(line);
	return (fd);
}

int	heredoc(char **str, int i, int *fd, t_prompt_info *data)
{
	int		index;
	int		len[2];
	char	*end_word;

	len[0] = i;
	len[1] = 0;
	len_file(*str, i, &len[0], &len[1]);
	index = i + 2;
	while (ft_isspace((*str)[index]))
		index++;
	end_word = ft_substr(*str, index, len[1] - index);
	if (!end_word)
		return (-1);
	*fd = read_write(*fd, end_word, data);
	if (*fd == -1)
		return (-1);
	*str = del_rd(*str, len);
	if (!(*str))
		return (-1);
	return (*fd);
}
