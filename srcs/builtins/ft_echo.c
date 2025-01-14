/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:42:41 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/14 18:25:17 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *join_prompt(char **prompt, int i)
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

/* static void	print_args(char **prompt, int s)
{
	char *result;

	if (prompt[s][0] == '\'')
		result = handle_quote();
	else if (prompt[s][0] == '\"')
		result = handle_quote();
	else if (prompt[s][0] == '$')
		result = handle_dollar();
	else
		result = join_prompt(prompt, s);
} */

void	ft_echo(char **prompt)
{
	//1. Gerer les ''
	//2. gerer les ""
	//3. gerer les $
	//4. gerer l'option -n
	if (!prompt[1])
	{
		ft_putstr_fd("\n", 0);
		return ;
	}
	if (prompt[1][0] == '-' && prompt[1][1] == 'n')
	{
		if (prompt[2])
			ft_putstr_fd(prompt[2], 0);
		else
			ft_putstr_fd("\n", 0);
		return ;
	}
	//5. gerer les cas speciaux
	ft_putstr_fd(prompt[1], 0);
	ft_putstr_fd("\n", 0);
}

int main(int argc, char **argv)
{
	char *result;

	(void)argc;
	result = join_prompt(argv, 1);
	printf("result : %s\n", result);
	free(result);
}
