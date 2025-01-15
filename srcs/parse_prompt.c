/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:24:15 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/15 16:29:44 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char *reverse_split(char **prompt, int i)
{
	char *result;
	char *temp;

	result = malloc(sizeof(char) * (ft_strlen(prompt[i]) + 1));
	if (!result)
		return (NULL);
	if (ft_strlcpy(result, prompt[i], ft_strlen(prompt[i]) + 1) == 0)
		return (NULL);
	i++;
	while (prompt[i])
	{
		temp = ft_strjoin(result, " ");
		if (!temp)
			return (NULL);
		free(result);
		result = ft_strjoin(temp, prompt[i]);
		if (!result)
			return (NULL);
		free(temp);
		i++;
	}
	return (result);
}

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
	while (str[i])
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

char *handle_dollar(char *str, char *c, int nb_doll)
{
	int i;
	int ienv;
	int itemp;
	char *env;
	char *temp;
	char *res;

	if (*c == "\'")
		return (NULL);
	i = 0;
	itemp = 0;
	ienv = 0;
	while (str[i] && nb_doll > 0)
	{
		if (str[i] == '$')
		{
			i++;
			while (str[i] && str[i] != '$')
			{
				env[ienv] = str[i];
				i++;
				ienv++;
			}
			res = better_join(temp, getenv(env), c);
			nb_doll--;
		}
		// mettre dans temp le res si plusieurs $
		if (!res)
			temp[itemp] = str[i];
		else
			temp = ft_strdup(res);
		i++;
	}
}

char *better_join(char *s1, char *s2, char *c)
{
	int ires;
	char *res;

	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)));
	ires = 0;
	fill_in_result(s1, res, &ires, c);
	//free(s1);
	fill_in_result(s2, res, &ires, c);
	//free(s2);
	return (res);
}

char *pars_prompt(char **prompt, int s)
{
	int		i;
	char	*env;
	char	*temp;
	char	*res;
	char	c;

	c = 0;
	if (prompt[s][0] != '$')
		res = ft_strdup(prompt[s]);
	while (prompt[s])
	{
		if (count_doll(prompt[s]) > 0)
			env = handle_dollars(prompt[s], &c);
		else if (env)
			res = better_join(temp, env, &c);
		else
			res = better_join(temp, prompt[s], &c);
		temp = ft_strdup(res);
		free(res);
		s++;
	}
}

int main(void)
{
	char *str1 = "Je teste ";
	char *str2= "ma fonctoin";
	char *res;
	char c = 0;

	res = better_join(str1, str2, &c);
	printf("res : %s", res);
}
