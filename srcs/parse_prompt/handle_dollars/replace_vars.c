/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:16:15 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/18 15:52:08 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char *get_var_name(char *prompt, int *i)
{
	int countc;
	char *res;
	int ires;

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
	res = malloc(sizeof(char) * (countc + 2));
	*i -= countc;
	countc += *i;
	while (*i < countc)
	{
		res[ires] = prompt[*i];
		ires++;
		(*i)++;
	}
	return (res[ires] = '\0', res);
}

char *add_env(char *prompt, int *i, int *ires, char *res)
{
	char *var_name;
	char *env;
	char *temp;

	temp = malloc(sizeof(char) * (*i + 1));
	ft_strlcpy(temp, res, *i + 1);
	var_name = get_var_name(prompt, i);
	env = getenv(var_name);
	if (!env)
		return (res);
	free(res);
	res = ft_strjoin(temp, env);
	(*ires) += strlen(env);
	free(temp);
	return (res);
}

int exist_closing(char *prompt, char c, int i)
{
	static int in_quote = 0;

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
	int quote_status;

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

char *check_dollars(char *prompt)
{
	int i;
	int ires;
	int in_single;
	int in_double;
	char *res;

	i = 0;
	ires = 0;
	in_single = 0;
	in_double = 0;
	res = malloc(sizeof(char) * (ft_strlen(prompt) + 1));
	while (prompt[i])
	{
		if ((prompt[i] == '\'' || prompt[i] == '\"'))
			update_quote(&in_single, &in_double, &i, prompt);
		if (prompt[i] == '$' && in_single == 0)
			res = add_env(prompt, &i, &ires, res);
		if (prompt[i] != '\"' || !in_double)
		{
			res[ires] = prompt[i];
			ires++;
			i++;
		}
	}
	return (res);
}
