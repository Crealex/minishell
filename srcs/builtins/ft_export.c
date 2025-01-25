/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:35:36 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/25 11:19:03 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *format_content(char *str)
{
	int		i;
	int		ires;
	int		quote[2];
	char	*res;

	i = 0;
	ires = 0;
	quote[0] = 0;
	quote[1] = 0;
	res = malloc(sizeof(char) * ft_strlen(str));
	while (str[i] != '=')
		res[ires++] = str[i++];
	while(str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			update_quote(&quote[0], &quote[1], &i, str);
		res[ires++] = str[i++];
	}
	res[ires] = '\0';
	free(str);
	return (res);
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
	//freesplit(temp); double free quand actif, pourquoi?
}

void	add_to_env(char *str, char ***env)
{
	int i;

	i = 0;
	if (is_quote(str))
		rm_quote(&str);
	if (check_name(str) == 1) //Gere le =
	{
		str = format_content(str);
		if (var_exist(str, *env))
			modify_var(str, env);
		else
			add_var(env, &i, str);
	}
	else if (check_name(str) == 2) // Gere le +=
	{
		str = format_content(str);
		if (var_exist(str, *env))
			cat_var(str, env); // a coder
		else
			add_var(env, &i, str);
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
	printf("test\n");
}
