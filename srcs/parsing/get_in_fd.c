/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_in_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:15:33 by dvauthey          #+#    #+#             */
/*   Updated: 2025/02/13 11:43:36 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	len_file(char *str, int i, int *start, int *end)
{
	*start = i;
	i++;
	if (str[i] == '<')
		i++;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && !ft_isspace(str[i]))
		i++;
	*end = i;
}

static int	open_fd(char *str, int fd_arg, int *len)
{
	int		fd;
	char	*str_cut;
	int		s;

	if (fd_arg > 2)
		close(fd_arg);
	s = len[0];
	s++;
	while (str[s] && ft_isspace(str[s]))
		s++;
	str_cut = ft_substr(str, s, len[1] - s);
	fd = open(str_cut, O_RDONLY);
	if (fd == -1)
		printf("minishell: %s: No such file or directory\n", str_cut);
	free(str_cut);
	return (fd);
}

char	*del_rd(char *str, int *len)
{
	int		i;
	int		j;
	char	*new;
	int		len_str;

	i = 0;
	j = 0;
	len_str = ft_strlen(str);
	new = ft_calloc(len_str - (len[1] - len[0]) + 1, sizeof(char));
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (i == len[0])
			while (i < len[1])
				i++;
		new[j] = str[i];
		i++;
		j++;
	}
	new[j] = '\0';
	free(str);
	return (new);
}

int	get_in_fd(char **str, int fd)
{
	int		i;
	int		quote[2];
	int		len[2];

	init_fd(&i, &len[0], &len[1]);
	init_two(&quote[0], &quote[1]);
	while ((*str)[i])
	{
		update_quote(&quote[0], &quote[1], &i, *str);
		if (!quote[0] && !quote[1] && (*str)[i] == '<' && (*str)[i + 1] != '<')
		{
			len_file(*str, i, &len[0], &len[1]);
			fd = open_fd(*str, fd, len);
			if (fd == -1)
				return (-1);
			*str = del_rd(*str, len);
			if (!(*str))
				return (-1);
		}
		if (!quote[0] && !quote[1] && (*str)[i] == '<' && (*str)[i + 1] == '<')
			heredoc(str, i);
		i++;
	}
	return (fd);
}
