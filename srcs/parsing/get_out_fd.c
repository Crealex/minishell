/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_out_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:08:33 by dvauthey          #+#    #+#             */
/*   Updated: 2025/03/11 16:12:14 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	len_file_out(char *str, int i, int *start, int *end)
{
	int	quote[2];

	init_two(&quote[0], &quote[1]);
	*start = i;
	i++;
	if (str[i] == '>')
		i++;
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (str[i])
	{
		update_quote(&quote[0], &quote[1], &i, str);
		if (!str[i])
			break ;
		if (!quote[0] && !quote[1] && isspace(str[i]))
			break ;
		i++;
	}
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
	s = len[0] + 1;
	if (str[s] == '>')
		s++;
	while (str[s] && ft_isspace(str[s]))
		s++;
	str_cut = filename(str, s);
	if (!str_cut)
		return (-1);
	if (!is_double)
		fd = open(str_cut, O_WRONLY | O_CREAT | O_TRUNC, 0744);
	else
		fd = open(str_cut, O_WRONLY | O_CREAT | O_APPEND, 0744);
	if (fd == -1)
	{
		print_err("minishell: ", NULL, NULL);
		perror(str_cut);
	}
	free(str_cut);
	return (fd);
}

int	get_out_fd(char **str, int fd, t_prompt_info *data, int c)
{
	int		len[2];
	int		isdouble;

	init_fd(&len[0], &len[1], &isdouble);
	*str = expansion(*str, data);
	len_file_out(*str, c, &len[0], &len[1]);
	is_double((*str)[c + 1], &isdouble);
	fd = open_fd(*str, fd, len, isdouble);
	*str = del_rd(*str, len, &c);
	if (!(*str))
		return (-1);
	if (fd == -1)
		return (-1);
	return (fd);
}
