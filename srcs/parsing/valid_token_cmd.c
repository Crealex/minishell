/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_token_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:29:11 by atomasi           #+#    #+#             */
/*   Updated: 2025/03/17 11:43:47 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stddef.h>

static int	len_token(char *str)
{
	int	i;
	int	quote[2];

	i = 0;
	quote[0] = 0;
	quote[1] = 0;
	while (str[i])
	{
		if (str[i] && ((str[i] == '\'' && !quote[1])
			|| (str[i] == '\"' && !quote[0])))
			update_quote(&quote[0], &quote[1], &i, str);
		if (!str[i] || (str[i] == ' ' && !quote[0] && !quote[1]))
			break ;
		i++;
	}
	return (i + 1);
}

static char	*extract_token(char *str)
{
	int		i;
	int		ires;
	char	*res;
	int		quote[2];

	i = 0;
	ires = 0;
	quote[0] = 0;
	quote[1] = 0;
	res = ft_calloc(sizeof(char), len_token(str));
	if (!res)
		return (res);
	while (str[i])
	{
		if (str[i] && ((str[i] == '\'' && !quote[1])
				|| (str[i] == '\"' && !quote[0])))
			update_quote(&quote[0], &quote[1], &i, str);
		if (str[i] == '\0' || (str[i] == ' ' && !quote[0] && !quote[1]))
			break ;
		res[ires++] = str[i++];
	}
	res[ires] = '\0';
	return (res);
}

static int	is_valid_builtins(char *token_cmd, size_t len_tok)
{
	if (!ft_strncmp("echo", token_cmd, len_tok))
		return (1);
	else if (!ft_strncmp("cd", token_cmd, len_tok))
		return (1);
	else if (!ft_strncmp("pwd", token_cmd, len_tok))
		return (1);
	else if (!ft_strncmp("export", token_cmd, len_tok))
		return (1);
	else if (!ft_strncmp("unset", token_cmd, len_tok))
		return (1);
	else if (!ft_strncmp("env", token_cmd, len_tok))
		return (1);
	else if (!ft_strncmp("exit", token_cmd, len_tok))
		return (1);
	return (0);
}

int	valid_token_cmd(t_prompt_info *data)
{
	char	*token_cmd;
	int		len_tok;

	if (data->is_pipe == 0)
		token_cmd = extract_token(data->str_prt);
	else
		token_cmd = extract_token(data->pipe[data->pos_pipe]);
	if (!token_cmd)
		return (-1);
	len_tok = ft_strlen(token_cmd);
	if (is_valid_builtins(token_cmd, len_tok))
		return (free(token_cmd), 1);
	else if (check_validity(token_cmd, 1))
		return (free(token_cmd), 1);
	print_err(token_cmd, ": command not found\n", NULL);
	return (free(token_cmd), 0);
}
