/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:30:31 by alexandre         #+#    #+#             */
/*   Updated: 2025/01/15 22:03:13 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	result = malloc(sizeof(char) * countc - 2);
	if (!result)
		return (NULL);
	countc = 0;
	while (str[i] && str[i] != '$' && str[i] != ' ' && str[i] != '\"')
	{
		result[countc] = str[i];
		i++;
		countc++;
	}
	result[i] = '\0';
	return (result);
}

char	*insert_env(char *str, char *env_name)
{
	char *env;
	char *res;

	//printf("env : %s\n", env_name);
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

	if (*c == '\'')
		return (get_name_var(str));
	i = 0;
	//printf("entry in handle_dollar\n");
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
		if (str[i])
			temp = better_join(res, &str[i], c);
		while (str[i] && str[i] != '$')
			i++;
		//printf("in_while cacaca %s\n", res);
	}
	return (res);
}
