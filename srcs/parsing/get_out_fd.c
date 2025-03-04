/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_out_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:08:33 by dvauthey          #+#    #+#             */
/*   Updated: 2025/03/04 14:00:36 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	len_file_out(char *str, int i, int *start, int *end)
{
	*start = i;
	i++;
	if (str[i] == '>')
		i++;
	// if (!strncmp(str, "echo", 4) || !ft_strncmp(str, "/bin/echo", 9))
	// {
		while (str[i] && ft_isspace(str[i]))
			i++;
		while (str[i] && !ft_isspace(str[i]))
			i++;
		*end = i;
	// }
	// else
	// {
	// 	*end = is_cmd(str, i, ">");
	// 	while (!str[*end] || ft_isspace(str[*end]))
	// 		(*end)--;
	// 	(*end)++;
	// }
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
	s = len[0] + 1;
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
		print_err("minishell: ", str, ": No such file or directory\n");
	free(str_cut);
	return (fd);
}

int	get_out_fd(char **str, int fd)
{
	int		i;
	int		inquote[2];
	int		len[2];
	int		isdouble;

	init_fd(&i, &len[0], &len[1]);
	init_fd(&inquote[0], &inquote[1], &isdouble);
	while ((*str)[i])
	{
		update_quote(&inquote[0], &inquote[1], &i, *str);
		if (!inquote[0] && !inquote[1] && (*str)[i] == '>')
		{
			len_file_out(*str, i, &len[0], &len[1]);
			is_double((*str)[i + 1], &isdouble);
			fd = open_fd(*str, fd, len, isdouble);
			if (fd == -1)
				return (-1);
			*str = del_rd(*str, len, &i);
			if (!(*str))
				return (-1);
		}
		i++;
	}
	return (fd);
}

