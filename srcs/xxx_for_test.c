/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xxx_for_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:09:53 by alexandre         #+#    #+#             */
/*   Updated: 2025/01/22 21:34:48 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	rm_quote(char **str)
{
	int i;
	int ires;
	char *res;
	int quote;
	int quote2;

	i = 0;
	ires = 0;
	quote = 0;
	quote2 = 0;
	res = ft_calloc((ft_strlen(*str) + 1), sizeof(char));
	if (!res)
		return ;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'' || (*str)[i] == '\"')
			update_quote(&quote, &quote2, &i, *str);
		if (!(*str)[i])
			break;
		res[ires++] = (*str)[i++];
	}
	free(*str);
	printf("%s\n", res);
	*str = ft_strdup(res);
	if (!*str)
		return ;
	free(res);
}

int main()
{
	char *str = ft_strdup("\"Je teste la fonction\"");
	printf("avant : %s, quote ? %d\n", str, is_quote(str));
	rm_quote(&str);
	printf("apres : %s, quote ? %d\n", str, is_quote(str));
	free(str);
}