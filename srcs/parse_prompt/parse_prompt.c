/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:24:15 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/15 22:02:05 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int count_doll(char *str)
{
	int i;
	int dollars;

	dollars = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			dollars++;
		i++;
	}
	return (dollars);
}

void	fill_in_result(char *str, char *res, int *ires, char *c)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '$')
	{
		if (!*c && (str[i] == '\'' || str[i] == '\"'))
		{
			*c = str[i];
			i++;
		}
		if (*c && str[i] == *c)
		{
			*c = 0;
			i++;
		}
		if (str[i])
		{
			//printf("test : %d\n", *ires);
			res[*ires] = str[i];
			(*ires)++;
			i++;
		}
	}
}


char *better_join(char *s1, char *s2, char *c)
{
	int ires;
	char *res;

	if (s1 && s2)
		res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	else if (s1 && !s2)
		res = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	else if (!s1 && s2)
		res = malloc(sizeof(char) * (ft_strlen(s2) + 1));
	ires = 0;
	if (s1)
		fill_in_result(s1, res, &ires, c);
	//free(s1);
	if (s1 && s2)
	{
		res[ires] = ' ';
		ires++;
	}
	if (s2)
		fill_in_result(s2, res, &ires, c);
	//free(s2);
	return (res);
}

char *parse_prompt(char **prompt, int s)
{
	char	*env;
	char	*temp;
	char	*res;
	char	c;

	c = 0;
	res = NULL;
	temp = NULL;
	/* if (prompt[s][0] != '$')
	{
		res = ft_strdup(prompt[s]);
		s++;
	} */
	while (prompt[s])
	{
		if (res)
		{
			temp = ft_strdup(res);
			free(res);
		}
		if (count_doll(prompt[s]) > 0)
		{
			env = handle_dollar(prompt[s], &c);
			res = better_join(temp, env, &c);
		}
		else
			res = better_join(temp, prompt[s], &c);
		s++;
	}
	return (res);
}
