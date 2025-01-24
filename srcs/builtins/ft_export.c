/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:35:36 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/24 13:52:34 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *format_content(char *str)
{
	int	i
}

int	check_name(char *str)
{
	int i;

	i = 0;
	if (str[0] && ft_isdigit(str[0]))
			return (0);
	while (str[i])
	{
		if (str[i] == '=' && i > 0)
		{
			if (i > 0 && str[i - 1] == '+')
				return (2);
			return (1);
		}
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '+')
			return (0);
		i++;
	}
		return (0);

}

void	add_var(char ***env, int *i, char *str)
{
	char **temp;
	int len;

	len = 0;
	while((*env)[len])
		len++;
	temp = malloc(sizeof(char *) * (len + 2));
	if (!temp)
		return ;
	while ((*env)[*i])
	{
		temp[*i] = ft_strdup((*env)[*i]);
		(*i)++;
	}
	temp[*i] = ft_strdup(str);
	(*i)++;
	temp[*i] = NULL;
	*i = 0;
	freesplit(*env);
	*env = cpy_double_array(*env, temp);
	freesplit(temp);
}

void	add_to_env(char *str, char ***env)
{
	int i;

	i = 0;
	if (is_quote(str))
		rm_quote(&str);
	//printf("in add to env\n");
	if (check_name(str) == 1) //Gere le =
	{
		//1.formater le contenu de la var
		//2.Verifier si le nom de la var existe deja
		add_var(env, &i, str);
		printf("Juste avant des derniers dup\n");
	}
	else if (check_name(str) == 2) // Gere le +=
	{
		//1. formater le contenu de la var
		//2. Verifier si la  var existe
		//modify_env(str, env); // a faire
		printf("handle +=\n");
	}
	else
	{
		printf("not valid name\n");
		return ;
	}
}

void	ft_export(char **prompt, char ***env)
{
	int i;

	i = 1;
	if (!prompt[1])
	{
		//special_display_env(env); // a faire
		return ;
	}
	(void)env;
	while (prompt[i])
	{
		add_to_env(prompt[i], env);
		i++;
	}
}
