/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_out_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:08:33 by dvauthey          #+#    #+#             */
/*   Updated: 2025/02/13 10:49:24 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	len_file(char *str, int i, int *start, int *end)
{
	*start = i;
	i++;
	if (str[i] == '>')
		i++;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && !ft_isspace(str[i]))
		i++;
	*end = i;
}

static void	is_double(char c, int *isdouble)
{
	if (c && c == '>')
		*isdouble = 1;
	else
		*isdouble = 0;
}

static int	open_fd(char *str, int fd_arg, int *len, int is_double)
{
	int		fd;
	char	*str_cut;
	int		s;

	if (fd_arg > 2)
		close(fd_arg);
	s = len[0];
	s++;
	if (str[s] == '>')
		s++;
	while (str[s] && ft_isspace(str[s]))
		s++;
	str_cut = ft_substr(str, s, len[1] - s);
	if (!str_cut)
		return (-1);
	if (!is_double)
		fd = open(str_cut, O_WRONLY | O_CREAT | O_TRUNC, 0744);
	else
		fd = open(str_cut, O_WRONLY | O_CREAT | O_APPEND, 0744);
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

int	get_out_fd(char **str, int fd)
{
	int		i;
	int		inquote[2];
	int		len[2];
	int		isdouble;

	init_fd(&i, &len[0], &len[1]);
	init_two(&inquote[0], &inquote[1]);
	isdouble = 0;
	while ((*str)[i])
	{
		update_quote(&inquote[0], &inquote[1], &i, *str);
		if (!inquote[0] && !inquote[1] && (*str)[i] == '>')
		{
			len_file(*str, i, &len[0], &len[1]);
			printf("len : %i, %i\n", len[0], len[1]);
			is_double((*str)[i + 1], &isdouble);
			fd = open_fd(*str, fd, len, isdouble);
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

