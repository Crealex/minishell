/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:16:15 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/31 16:00:27 by dvauthey         ###   ########.fr       */
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
	if (ft_strncmp(var_name, "?", ft_strlen(var_name)) == 0)
	{
		(*i)++;
		env = ft_itoa(update_exit_code(-1));
	}
	else
		env = getenv(var_name);
	free(var_name);
	if (!env)
		return (res);
	if (res)
		free(res);
	res = better_strjoin(temp, env, prompt, *i);
	(*ires) += strlen(env);
	if (temp)
		free(temp);
	return (res);
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
	return (free(prompt), res);
}
