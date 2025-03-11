/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_token_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:29:11 by atomasi           #+#    #+#             */
/*   Updated: 2025/03/11 13:20:15 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	len_token(char *str)
{
	int	i;
	int	quote[2];

	i = 0;
	quote[0] = 0;
	quote[1] = 0;
	while (str[i])
	{
		if (str[i] == (str[i] == '\'' && !quote[1])
			|| (str[i] == '\"' && !quote[0]))
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
		if (!str[i] || (str[i] == ' ' && !quote[0] && !quote[1]))
			break ;
		res[ires++] = str[i++];
	}
	res[ires] = '\0';
	return (res);
}

int	valid_token_cmd(t_prompt_info *data)
{
	char	*token_cmd;
	int		len_tok;

	token_cmd = extract_token(data->str_prt);
	if (!token_cmd)
		return (-1);
	len_tok = ft_strlen(token_cmd);
	if (!ft_strncmp("echo", token_cmd, len_tok))
		return (free(token_cmd), 1);
	else if (!ft_strncmp("cd", token_cmd, len_tok))
		return (free(token_cmd), 1);
	else if (!ft_strncmp("pwd", token_cmd, len_tok))
		return (free(token_cmd), 1);
	else if (!ft_strncmp("export", token_cmd, len_tok))
		return (free(token_cmd), 1);
	else if (!ft_strncmp("unset", token_cmd, len_tok))
		return (free(token_cmd), 1);
	else if (!ft_strncmp("env", token_cmd, len_tok))
		return (free(token_cmd), 1);
	else if (!ft_strncmp("exit", token_cmd, len_tok))
		return (free(token_cmd), 1);
	else if (check_validity(token_cmd, 1))
		return (free(token_cmd), 1);
	print_err(token_cmd, ": command not found\n", NULL);
	return (free(token_cmd), 0);
}
