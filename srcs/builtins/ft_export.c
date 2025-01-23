/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:35:36 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/23 21:02:55 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_str(char *str)
{
	int i;
	int is_egal;

	i = 0;
	is_egal = 0;
	if (!str[i] || ((str[i] < 'A' || str[i] > 'Z')
			&& (str[i] < 'a' || str[i] > 'z') && str[i] != '_'))
			return (0);
	while (str[i])
	{
		if (str[i] == '=')
		{
			if (i > 0)
				is_egal++;
			if (i > 0 && str[i - 1] == '+')
				return (2);
			break;
		}
		if (((str[i] < '0' || str[i] > '9') && ((str[i] < 'A' || str[i] > 'Z'))
			&& (str[i] < 'a' || str[i] > 'z') && str[i] != '_') && str[i] != '=') // tester les caracteres interdit
			return (0);
		i++;
	}
	printf("in check str\n");
	if (is_egal <= 0)
		return (0);
	return (1);
}

void	add_space_darray(char ***env, int *i)
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
	(*i)++;
	temp[*i] = NULL;
	*i = 0;
	freesplit(*env);
	//printf("test\n");
	while (temp[*i])
	{
		(*env)[*i] = ft_strdup(temp[*i]);
		(*i)++;
	}
	freesplit(temp);
}

void	add_to_env(char *str, char ***env)
{
	int i;

	i = 0;
	if (is_quote(str))
		rm_quote(&str);
	//printf("in add to env\n");
	if (check_str(str) == 1) //Gere le = |||| a tester
	{
		add_space_darray(env, &i);
		i--;
		(*env)[i] = ft_strdup(str);
	}
	else if (check_str(str) == 2) // Gere le += |||| a tester
	{
		//modify_env(str, env); // a faire
		printf("handle +=\n");
	}
	else
		return ;
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
