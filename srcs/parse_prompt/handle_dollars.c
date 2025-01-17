/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:30:31 by alexandre         #+#    #+#             */
/*   Updated: 2025/01/17 16:42:40 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_occurence(char *str, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

char *get_name_var(char *str)
{
	int i;
	int countc;
	char *result;

	i = 0;
	countc = 0;
	while(str[i] && str[i] != '$')
		i++;
	i++;
	while (str[i + countc] && str[i + countc] != '$'
		&& str[i + countc] != ' ' && str[i + countc] != '\"')
		countc++;
	result = malloc(sizeof(char) * countc);
	if (!result)
		return (NULL);
	countc = 0;
	while (str[i] && str[i] != '$' && str[i] != ' ' && str[i] != '\"')
	{
		result[countc] = str[i];
		i++;
		countc++;
	}
	result[countc] = '\0';
	return (result);
}

char	*insert_env(char *str, char *env_name)
{
	char *env;
	char *res;

	env = getenv(env_name);
	if (!env)
		return (str);
	if (!str)
	{
		res = ft_strdup(env);
		free(env_name);
		return (res);
	}
	res = ft_strjoin(str, env);
	free(str);
	free(env_name);
	return (res);
}

char *handle_dollar(char *str, char *c)
{
	int i;
	char *env;
	char *temp;
	char *res;

	if (*c == '\'' || (str[0] == '\'' && count_occurence(str, '\'') % 2 == 0))
		return (ft_strjoin("$", get_name_var(str)));
	i = 0;
	temp = NULL;
	res = NULL;
	while (str[i])
	{
		if (str[i] == '$')
		{
			env = get_name_var(&str[i]);
			res = insert_env(temp, env);
			i++;
			while (str[i] && str[i] != '$')
				i++;
		}
		if ((str[i] && str[i] != *c && (*c || (str[i] != '\'' && str[i] != '\"'))) || count_occurence(str, *c) != 2)
		{
			temp = better_join(res, &str[i], c);
			while (str[i] && str[i] != '$')
				i++;
		}
		else
			i++;
	}
	return (res);
}
