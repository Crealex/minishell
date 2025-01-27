/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 20:29:14 by alexandre         #+#    #+#             */
/*   Updated: 2025/01/27 16:03:21 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_name(char *str)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	res = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*get_content(char *str)
{
	int		i;
	int		ires;
	int		count;
	int		quote[2];
	char	*res;

	i = 0;
	ires = 0;
	count = 0;
	quote[0] = 0;
	quote[1] = 0;
	while (str[i] && str[i] != '=')
		i++;
	i++;
	while (str[i + count])
		count++;
	res = malloc(sizeof(char) * count);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			update_quote(&quote[0], &quote[1], &i, str);
		if (str[i])
			res[ires++] = str[i++];
	}
	return (res[ires] = '\0', res);
}

int var_exist(char *str, char **env)
{
	int		i;
	int		l_name;
	char	*name;

	i = 0;
	name = get_name(str);
	l_name = ft_strlen(name);
	while (env[i])
	{
		if (ft_strncmp(name, env[i], l_name) == 0)
			return (i);
		i++;
	}
	free(name);
	return (-1);
}

void	modify_var(char *str, char ***env)
{
	int		ienv;
	ienv = var_exist(str, *env);
	printf("env[ienv] before dup : %s\n", (*env)[ienv]);
	if((*env)[ienv])
		free((*env)[ienv]);
	(*env)[ienv] = ft_strdup(str);
	printf("env[ienv] after dup : %s\n", (*env)[ienv]);
}

void	cat_var(char *str, char ***env)
{
	int		ienv;
	char	*content;
	char	*temp;

	//1. stocker la content a ajouter (str apres le =)
	content = get_content(str);
	//2. Trouver la bonne variable d'env
	ienv = var_exist(str, *env);
	//3. Join l'env avec le bout de str
	temp = ft_strdup((*env)[ienv]);
	free((*env)[ienv]);
	(*env)[ienv] = ft_strjoin(temp, content);
	free(temp);
}