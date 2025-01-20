/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:16:15 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/20 19:23:52 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_var_name(char *prompt, int *i)
{
	int		countc;
	char	*res;
	int		ires;

	(*i)++;
	countc = *i;
	ires = 0;
	if ((prompt[*i] >= '0' && prompt[*i] <= '9') && prompt[*i] != '_')
		return (NULL);
	while (prompt[*i] && ((prompt[*i] >= 'A' && prompt[*i] <= 'Z')
			|| (prompt[*i] >= 'a' && prompt[*i] <= 'z') || (prompt[*i] >= '0'
				&& prompt[*i] <= '9') || prompt[*i] == '_'))
		(*i)++;
	countc = *i - countc;
	res = ft_calloc(countc + 1, sizeof(char));
	if (!res)
		return (NULL);
	*i -= countc;
	countc += *i;
	while (*i < countc)
		res[ires++] = prompt[(*i)++];
	return (res[ires] = '\0', res);
}

char	*add_env(char *prompt, int *i, int *ires, char *res)
{
	char	*var_name;
	char	*env;
	char	*temp;

	temp = ft_calloc(*i + 1, sizeof(char));
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, res, *ires + 1);
	var_name = get_var_name(prompt, i);
	env = getenv(var_name);
	free(var_name);
	if (!env)
		return (res);
	if (res)
		free(res);
	res = ft_strjoin(temp, env);
	(*ires) += strlen(env);
	if (temp)
		free(temp);
	return (res);
}

int	exist_closing(char *prompt, char c, int i)
{
	static int	in_quote = 0;

	if (in_quote == 1)
	{
		in_quote = 0;
		return (2);
	}
	else if (in_quote == 0)
	{
		while (prompt[i])
		{
			i++;
			if (prompt[i] == c)
			{
				in_quote++;
				return (1);
			}
		}
	}
	return (0);
}

void	update_quote(int *in_single, int *in_double, int *i, char *prompt)
{
	int	quote_status;

	if (prompt[*i] == '\'' && !*in_double)
	{
		quote_status = exist_closing(prompt, '\'', *i);
		if (quote_status == 0)
			return ;
		else if (quote_status == 1)
			*in_single = 1;
		else if (quote_status == 2)
			*in_single = 0;
		(*i)++;
	}
	else if (prompt[*i] == '\"' && !*in_single)
	{
		quote_status = exist_closing(prompt, '\"', *i);
		if (quote_status == 0)
			return ;
		else if (quote_status == 1)
			*in_double = 1;
		else if (quote_status == 2)
			*in_double = 0;
		(*i)++;
	}
}

char	*handle_dollars(char *prompt)
{
	int		i;
	int		ires;
	int		in_single;
	int		in_double;
	char	*res;

	i = 0;
	ires = 0;
	in_single = 0;
	in_double = 0;
	res = ft_calloc((ft_strlen(prompt) + 1), sizeof(char));
	if (!res)
		return (NULL);
	while (prompt[i])
	{
		if ((prompt[i] == '\'' || prompt[i] == '\"'))
			update_quote(&in_single, &in_double, &i, prompt);
		if (prompt[i] == '$' && in_single == 0)
			res = add_env(prompt, &i, &ires, res);
		if (prompt[i] && (prompt[i] != '\"' || !in_double)
			&& (prompt[i] != '$' || in_single))
			res[ires++] = prompt[i++];
	}
	res[ires] = '\0';
	return (res);
}
