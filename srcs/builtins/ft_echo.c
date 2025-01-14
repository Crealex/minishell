/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:42:41 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/14 22:44:21 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// tout revoir et imprimer caractere par caractere plus que une string par string

static char *join_prompt(char **prompt, int i)
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

static char *handle_dollar(char **prompt, int i) // a revoir pour opti, les free etc...
{
	char *temp;
	char **tab;
	char *env;
	char *result = "gestion du dollar";
	int j;

	j = 0;
	while (prompt[i])
	{
		if (prompt[i][j] == '$')
		{
			tab = ft_split(prompt[i], '$');
			temp = ft_strdup(tab[0]);
			env = ft_strdup(tab[1]);
			tab = ft_split(tab[1], ' ');
			free(env);
			free(temp);
			env = ft_strdup(tab[0]);
		}
		if (!prompt[i][j])
			i++;
	}
	result = getenv(tab[0]);
	return (result);
}

static char *handle_quote(char **prompt, int i, char c) // a tester partout enfate et pas uniquement avec une quote au debut
{
	char *result;
	char *line;
	int ires;
	int quote;

	ires = 0;
	quote = 0;
	line = join_prompt(prompt, i);
	result = malloc(sizeof(char) * ft_strlen(line));
	while (line[ires + quote])
	{
		if (line[ires + quote] == c)
			quote++;
		result[ires] = line[ires + quote];
		ires++;
	}
	result[ires] = '\0';
	if (quote % 2 != 0)
		printf("nombre impaire de quote\n"); // trouver comment ouvrir l'ecoute
	return (result);
}

static void	print_args(char **prompt, int s)
{
	char *result;

	if (prompt[s][0] == '\'')
		result = handle_quote(prompt, s, '\'');
	else if (prompt[s][0] == '\"')
		result = handle_quote(prompt, s, '\"');
	//else if (prompt[s][0] == '$')
		result = handle_dollar(prompt, s);
	//else
		//result = join_prompt(prompt, s);
	ft_putstr_fd(result, 1);
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

/* int main(int argc, char **argv)
{
	char *result;

	(void)argc;
	result = join_prompt(argv, 1);
	printf("result : %s\n", result);
	free(result);
} */
