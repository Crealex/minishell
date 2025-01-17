/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:24:15 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/17 20:40:09 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//!!!Pas utilisee mais peut-etre des fonctions utiles!!!

void	fill_in_result(char *str, char *res, int *ires, char *c)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '$')
	{
		if (!*c && (str[i] == '\'' || str[i] == '\"'))
		{
			*c = str[i];
			if (count_occurence(str, *c) % 2 == 0)
				i++;
		}
		if (*c && str[i] == *c && count_occurence(str, *c) % 2 == 0)
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
	res[ires] = '\0';
	return (res);
}

/* char *parse_prompt(char **prompt, int s)
{
	char	*env;
	char	*temp;
	char	*res;
	char	c;

	c = 0;
	res = NULL;
	temp = NULL;
	while (prompt[s])
	{
		if (res)
		{
			temp = ft_strdup(res);
			free(res);
		}
		if (count_occurence(prompt[s], '$') > 0 && count_occurence(prompt[s], '\'') != 2)
		{
			env = handle_dollar(prompt[s], &c);
			//printf("temp in parse_prompt : %s\n", temp);
			printf("env in parse_prompt : %s\n", env);
			if (env)
				res = better_join(temp, env, &c);
			printf("res in parse ptompt : %s\n", res);
		}
		else
			res = better_join(temp, prompt[s], &c);
		s++;
	}
	return (res);
} */
