/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:42:41 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/15 15:57:07 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// tout revoir et imprimer caractere par caractere plus que une string par string
/*
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

static int	handle_dollar(char *prompt, int i)
{
	char *env;
	int ienv;

	ienv = i;
	while (prompt[ienv] && prompt[ienv] != ' ')
		ienv++;
	env = malloc(sizeof(char) * (ienv - i));
	ienv = 0;
	while (prompt[i] && prompt[i] != ' ')
	{
		env[ienv] = prompt[i];
		ienv++;
		i++;
	}
	ft_putstr_fd(getenv(env), 1);
	return (i - 1);
}


static void print_args(char **prompt, int s)
{
	char *prompt_str;
	char *result;
	int i;
	char c;

	i = 0;
	prompt_str = reverse_split(prompt, s);
	result = malloc(sizeof(char) * sft_strlen(prompt_str));
	c = '\0';
	while (prompt_str[i])
	{
		if (!c && (prompt_str[i] == '\'' || prompt_str[i] == '\"'))
		{
			c = prompt_str[i];
			i++;
		}
		else if (c != '\'' && prompt_str[i] == '$')
			i = handle_dollar(prompt_str, i);
		else if (c && prompt_str[i] == c)
			i++;
		//printf("tetstetstets\n");
		ft_putchar_fd(prompt_str[i], 1);
		i++;
	}
}

void	ft_echo(char **prompt)
{
	//1. Gerer les ''
	//2. gerer les ""
	//3. gerer les $
	//4. gerer l'option -n
	//5. gerer les cas speciaux

	if (!prompt[1])
	{
		ft_putstr_fd("\n", 1);
		return ;
	}
	if (prompt[1][0] == '-' && prompt[1][1] == 'n')
	{
		if (prompt[2])
			print_args(prompt, 2);
		else
			ft_putstr_fd("\n", 1);
		return ;
	}
	print_args(prompt, 1);
	ft_putstr_fd("\n", 1);
}


*/