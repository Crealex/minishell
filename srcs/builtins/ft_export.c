/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:35:36 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/29 15:58:44 by atomasi          ###   ########.fr       */
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
	res = malloc(sizeof(char) * (len_wquote(str) + 1));
	while (str[i] && str[i] != '=')
		res[ires++] = str[i++];
	while(str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			update_quote(&quote[0], &quote[1], &i, str);
		if (str[i])
			res[ires++] = str[i++];
	}
	res[ires] = '\0';
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
		if (str[i] == '=')
			return (1);
		else if (str[i] == '+')
		{
			i++;
			if (str[i] == '=')
				return (2);
			return (0);
		}
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
		return (-1);

}

void	add_var(char ***env, int *i, char *str, int plus)
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
	if (plus == 0)
		temp[*i] = ft_strdup(str);
	else
		temp[*i] = remove_plus(str);
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
	if (check_name(str) == 1) //Gere le =
	{
		str = format_content(str);
		if (var_exist(str, *env) != -1)
			modify_var(str, env);
		else
			add_var(env, &i, str, 0);
		free(str);
	}
	else if (check_name(str) == 2) // Gere le += // ATTENTION A ENLEVER LE PLUS +
	{
		str = format_content(str);
		if (var_exist(str, *env) != -1)
			cat_var(str, env);
		else
			add_var(env, &i, str, 1);
		free(str);
	}
	else if (check_name(str) == 0)
		printf("minishell: export: `%s': not a valid identifier\n", str);
}

void	ft_export(char **prompt, char ***env)
{
	int i;

	i = 1;
	if (!prompt[1])
	{
		display_sort(*env);
		return ;
	}
	(void)env;
	while (prompt[i])
	{
		add_to_env(prompt[i], env);
		i++;
	}
}
