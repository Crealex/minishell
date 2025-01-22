/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_wquote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:40:46 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/22 16:26:19 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	counter_space(char *s)
{
	int	count;
	int	i;
	int in_single;
	int in_double;

	i = 0;
	count = 0;
	in_single = 0;
	in_double = 0;
	while (s[i])
	{
		while (s[i] == ' ' && i > 0 && s[i - 1] == ' ')
			i++;
		if (s[i] == '\'' || s[i] == '\"')
			update_quote(&in_single, &in_double, &i, s);
		if (s[i] == ' ' && (!in_single && !in_double))
		{
			count++;
		}
		if (s[i])
			i++;
	}
	return (count);
}

int	len_to_space(char *str, int i)
{
	int count;
	int in_single;
	int in_double;

	count = 0;
	in_single = 0;
	in_double = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			update_quote(&in_single, &in_double, &i, str);
		if (str[i] == 32 && (!in_single && !in_double))
			return (count);
		i++;
		count++;
	}
	return (count);
}

static int	malloc_words(char **res, char *s, int in_s, int in_d)
{
	int	word;
	int	countl;
	int	i;

	word = 0;
	i = 0;
	while (s[i])
	{
		countl = 0;
		while (s[i] == ' ' && !in_s && !in_d)
			i++;
		countl = len_to_space(s, i);
		if (countl > 0)
		{
			res[word] = malloc(countl + 1);
			if (!res[word++])
				return (0);
		}
		i += countl;
	}
	res[word] = NULL;
	return (1);
}

static void	fill(char **res, char *s, int in_s, int in_d)
{
	int	i;
	int	jres;
	int	ires;

	i = 0;
	jres = 0;
	ires = 0;
	while (s[i] == ' ')
		i++;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			update_quote(&in_s, &in_d, &i, s);
		if (s[i] == ' ' && !in_s && !in_d)
		{
			res[ires][jres] = '\0';
			ires++;
			jres = 0;
			while (s[i] == ' ')
				i++;
			continue ;
		}
		res[ires][jres++] = s[i++];
	}
	if (ires < counter_space(s))
		res[ires][jres] = '\0';
}

char	**split_wquote(char *s)
{
	char	**res;
	int		word_count;
	int		i;
	int in_single;
	int in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	if (!s)
		return (NULL);
	word_count = counter_space(s);
	res = malloc(sizeof(char *) * (word_count + 1));
	if (res == NULL)
		return (NULL);
	if (!malloc_words(res, s, in_single, in_double))
	{
		freesplit(res);
		return (NULL);
	}
	printf("s : %s\n", s);
	if (word_count > 0)
		fill(res, s, in_single, in_double);
	return (res);
}

int main()
{
	char *str;
	char **res;
	int i;

	i = 0;
	res = split_wquote(str);
	while (res[i] && i < 5)
	{
		printf("%s\n", res[i]);
		i++;
	}
}