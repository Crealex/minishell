/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 20:29:14 by alexandre         #+#    #+#             */
/*   Updated: 2025/01/26 21:07:07 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_name(char *str)
{
	int i;
	char *res;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	res = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] && str[i] != '=')
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
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
	return (0); // retourner -1 pluto que zero sinon risque de bug
}

void	modify_var(char *str, char ***env)
{
	int		ienv;

	ienv = var_exist(str, *env);
	free((*env)[ienv]);
	(*env)[ienv] = ft_strdup(str);
}

void	cat_var(char *str, char ***env)
{
	int i;

	i = 0;
	//1, stocker la content a ajouter (str apres le =)
	//2. Trouver la bonne variable d'env
	//3. Join l'env avec le bout de str
	(void)str;
	(void)env;
	printf("cat_var %d\n", i);
}