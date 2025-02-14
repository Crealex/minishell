/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:16:15 by atomasi           #+#    #+#             */
/*   Updated: 2025/02/13 14:41:07 by atomasi          ###   ########.fr       */
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
	if ((prompt[*i] >= '0' && prompt[*i] <= '9') && prompt[*i] != '_' && prompt[*i] != '?')
		return (NULL);
	while (prompt[*i] && ((prompt[*i] >= 'A' && prompt[*i] <= 'Z')
			|| (prompt[*i] >= 'a' && prompt[*i] <= 'z') || (prompt[*i] >= '0'
				&& prompt[*i] <= '9') || prompt[*i] == '_' || prompt[*i] == '?'))
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

char	*add_env(char *prompt, int *i, t_str *res, char **all_env)
{
	char	*var_name;
	char	*env;
	char	*temp;

	temp = ft_calloc(*i + 1, sizeof(char));
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, res->str, res->i + 1);
	var_name = get_var_name(prompt, i);
	if (ft_strncmp(var_name, "?", 1) == 0)
	{
		(*i)++;
		env = ft_itoa(update_exit_code(-1));
	}
	else if (var_name[0] == '\0')
		env = ft_strdup("$");
	else
		env = ft_getenv(var_name, all_env);
	free(var_name);
	if (!env)
		return (res->str);
	free(res->str);
	res->str = better_strjoin(temp, env, prompt, *i);
	(res->i) += strlen(env);
	return (free(temp), res->str);
}


char	*handle_dollars(char *prompt, char **env)
{
	int		i;
	int		in_single;
	int		in_double;
	t_str	res;

	i = 0;
	res.i = 0;
	in_single = 0;
	in_double = 0;
	res.str = ft_calloc((ft_strlen(prompt) + 1), sizeof(char));
	if (!res.str)
		return (NULL);
	while (prompt[i])
	{
		if ((prompt[i] == '\'' || prompt[i] == '\"') && ft_strchr(prompt, '$'))
			update_quote(&in_single, &in_double, &i, prompt);
		if (prompt[i] == '$' && in_single == 0)
			res.str = add_env(prompt, &i, &res, env);
		if (prompt[i] && (prompt[i] != '\"' || !in_double)
			&& (prompt[i] != '$' || in_single))
			res.str[res.i++] = prompt[i++];
	}
	res.str[res.i] = '\0';
	return (free(prompt), res.str);
}
