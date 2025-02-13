/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_in_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:15:33 by dvauthey          #+#    #+#             */
/*   Updated: 2025/02/13 10:39:15 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	len_file(char *str, int i, int *start, int *end)
{
	*start = i;
	i++;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && !ft_isspace(str[i]))
		i++;
	*end = i;
}

static int	open_fd(char *str, int fd_arg, int start, int end)
{
	int		fd;
	char	*str_cut;
	int		s;

	if (fd_arg > 2)
		close(fd_arg);
	s = start;
	s++;
	while (str[s] && ft_isspace(str[s]))
		s++;
	str_cut = ft_substr(str, s, end - s);
	fd = open(str_cut, O_RDONLY);
	if (fd == -1)
		printf("minishell: %s: No such file or directory\n", str);
	free(str_cut);
	return (fd);
}

static char	*del_rd(char *str, int start, int end)
{
	int		i;
	int		j;
	char	*new;
	int		len;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	new = ft_calloc(len - (end - start) + 1, sizeof(char));
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (i == start)
			while (i < end)
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
	int		inquote[2];
	int		len[2];

	init_fd(&i, &len[0], &len[1]);
	init_two(&inquote[0], &inquote[1]);
	while ((*str)[i])
	{
		update_quote(&inquote[0], &inquote[1], &i, *str);
		if (!inquote[0] && !inquote[1] && (*str)[i] == '<' && (*str)[i + 1]
			&& (*str)[i + 1] != '<')
		{
			len_file(*str, i, &len[0], &len[1]);
			fd = open_fd(*str, fd, len[0], len[1]);
			if (fd == -1)
				return (-1);
			*str = del_rd(*str, len[0], len[1]);
			if (!(*str))
				return (-1);
		}
		i++;
	}
	return (fd);
}
