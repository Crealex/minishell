/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:35:36 by atomasi           #+#    #+#             */
/*   Updated: 2025/03/10 10:41:48 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*format_content(char *str)
{
	int		i;
	int		ires;
	char	*res;

	i = 0;
	ires = 0;
	res = malloc(sizeof(char) * (len_wquote(str) + 1));
	while (str[i] && str[i] != '=')
		res[ires++] = str[i++];
	while (str[i])
	{
		if (str[i])
			res[ires++] = str[i++];
	}
	res[ires] = '\0';
	return (res);
}

static int	check_name(char *str)
{
	int	i;

	i = 0;
	if ((str[0] && ft_isdigit(str[0])) || str[0] == '=')
		return (update_exit_code(1), 0);
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		else if (str[i] == '+')
		{
			i++;
			if (str[i] == '=')
				return (2);
			return (update_exit_code(1), 0);
		}
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (update_exit_code(1), 0);
		i++;
	}
	return (-1);
}

void	add_var(char ***env, int *i, char *str, int plus)
{
	char	**temp;
	int		len;

	len = 0;
	while ((*env)[len])
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
	int	i;

	i = 0;
	if (check_name(str) == 1)
	{
		str = format_content(str);
		if (var_exist(str, *env) != -1)
			modify_var(str, env);
		else
			add_var(env, &i, str, 0);
		free(str);
	}
	else if (check_name(str) == 2)
	{
		str = format_content(str);
		if (var_exist(str, *env) != -1)
			cat_var(str, env);
		else
			add_var(env, &i, str, 1);
		free(str);
	}
	else if (check_name(str) == 0)
		print_err("minishell: export: `", str, "': not a valid identifier\n");
}

void	ft_export(char **prompt, char ***env)
{
	int	i;

	i = 1;
	if (!env || !*env)
		return ;
	if (!prompt[1])
	{
		display_sort(*env);
		return ;
	}
	while (prompt[i])
	{
		if (is_quote(prompt[i]))
			prompt[i] = rm_quote(prompt[i]);
		add_to_env(prompt[i], env);
		i++;
	}
}
