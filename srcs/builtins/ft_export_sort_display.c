/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_sort_display.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:24:42 by atomasi           #+#    #+#             */
/*   Updated: 2025/03/10 10:43:17 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	in_array(int num, int *incr)
{
	int	i;

	i = 0;
	while (incr[i] != -1)
	{
		if (incr[i] == num)
			return (1);
		i++;
	}
	return (0);
}

static int	next_smallest(int *index, char **env)
{
	int	i;
	int	smallest;

	i = 0;
	smallest = -1;
	while (env[i])
	{
		if (!in_array(i, index) && (smallest == -1
				|| ft_strncmp(env[i], env[smallest], ft_strlen(env[i])) < 0))
		{
			smallest = i;
		}
		i++;
	}
	return (smallest);
}

static char	**put_in_res(int *index, char **env)
{
	int		i;
	char	**res;
	char	*content;
	char	*temp;
	char	*name;

	i = 0;
	res = malloc(sizeof(char *) * (len_double_tab(env) + 1));
	while (index[i] != -1)
	{
		content = get_content(env[index[i]]);
		name = get_name(env[index[i]]);
		temp = ft_strjoin("\"", content);
		free(content);
		content = ft_strjoin(temp, "\"");
		free(temp);
		temp = ft_strjoin(name, "=");
		free(name);
		res[i] = ft_strjoin(temp, content);
		free(temp);
		free(content);
		i++;
	}
	res[i] = NULL;
	return (res);
}

static char	**sort_env(char **env)
{
	int		i;
	int		ii;
	int		*index;
	char	**res;

	index = malloc(sizeof(int) * (len_double_tab(env) + 1));
	ii = 0;
	i = 0;
	while (ii <= len_double_tab(env))
		index[ii++] = -1;
	ii = 0;
	while (env[i])
	{
		index[ii] = next_smallest(index, env);
		ii++;
		i++;
	}
	res = put_in_res(index, env);
	free(index);
	return (res);
}

void	display_sort(char **env)
{
	char	**res;
	int		i;

	if (!env)
		return ;
	res = sort_env(env);
	i = 0;
	while (res[i])
	{
		printf("declare -x ");
		printf("%s\n", res[i]);
		i++;
	}
	freesplit(res);
}
