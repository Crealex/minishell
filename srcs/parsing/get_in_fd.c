/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_in_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:15:33 by dvauthey          #+#    #+#             */
/*   Updated: 2025/03/04 17:55:55 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	is_cmd(char *str, int i, char *s)
// {
// 	int		index;
// 	int		index_space;
// 	char	*line;

// 	index = 0;
// 	line = NULL;
// 	index_space = i;
// 	while (str[i] && ft_isspace(str[i]))
// 		i++;
// 	while (str[i + index])
// 	{
// 		if (ft_isspace(str[i + index]) || !str[i + index + 1])
// 		{	
// 			if (!str[i + index + 1])
// 				index++;
// 			line = ft_substr(str, i, index);
// 			if (!line)
// 				return (0);
// 			if (!check_validity(line) && ft_strncmp(line, "|", 1)
// 				&& ft_strncmp(line, s, 1))
// 				return (free(line), is_cmd(str, i + index, s));
// 			else
// 				return (free(line), index_space);
// 		}
// 		index++;
// 	}
// 	return (index_space);
// }

void	len_file(char *str, int i, int *start, int *end)
{
	int	quote[2];

	init_two(&quote[0], &quote[1]);
	*start = i;
	i++;
	if (str[i] == '<')
		i++;
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (str[i])
	{
		update_quote(&quote[0], &quote[1], &i, str);
		if (!quote[0] && !quote[1] && isspace(str[i]))
			break ;
		i++;
	}
	*end = i;
}

static char	*filename(char *str, int i)
{
	char	*temp;
	int		quote[2];

	temp = ft_calloc(2, sizeof(char));
	if (!temp)
		return (NULL);
	init_two(&quote[0], &quote[1]);
	while (str[i])
	{
		update_quote(&quote[0], &quote[1], &i, str);
		if (str[i] && (str[i] == '\'' || str[i] == '\"'))
			continue ;
		if (!str[i] || (!quote[0] && !quote[1] && isspace(str[i])))
			return (temp);
		else
		{
			temp = char_strjoin(temp, str[i]);
			if (!temp)
				return (NULL);			
		}
		i++;
	}
	return (temp);
}

static int	open_fd(char *str, int fd_arg, int *len)
{
	int		fd;
	char	*str_cut;
	int		s;
	int		quote[2];

	init_two(&quote[0], &quote[1]);
	if (fd_arg > 2)
		close(fd_arg);
	s = len[0] + 1;
	while (str[s] && ft_isspace(str[s]))
		s++;
	str_cut = filename(str, s);
	if (!str_cut)
		return (-1);
	fd = open(str_cut, O_RDONLY);
	if (fd == -1)
		print_err("minishell: ", str_cut, ": No such file or directory\n");
	free(str_cut);
	return (fd);
}

char	*del_rd(char *str, int *len, int *index)
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
		if (str[i])
			new[j++] = str[i++];
	}
	new[j] = '\0';
	if (!str[i])
		(*index)--;
	free(str);
	return (new);
}

int	get_in_fd(char **str, int fd, t_prompt_info *data)
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
			*str = del_rd(*str, len, &i);
			if (!(*str))
				return (-1);
		}
		if (!quote[0] && !quote[1] && (*str)[i] == '<' && (*str)[i + 1] == '<')
			if (heredoc(str, i, &fd, data) == -1)
				return (-1);
		i++;
	}
	return (fd);
}
