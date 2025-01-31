/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xxx_for_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:09:53 by alexandre         #+#    #+#             */
/*   Updated: 2025/01/27 10:48:57 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_content(char *str)
{
	int		i;
	int		ires;
	int		count;
	int		quote[2];
	char	*res;

	i = 0;
	ires = 0;
	count = 0;
	quote[0] = 0;
	quote[1] = 0;
	while (str[i] && str[i] != '=')
		i++;
	i++;
	while (str[i + count])
		count++;
	res = malloc(sizeof(char) * count);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			update_quote(&quote[0], &quote[1], &i, str);
		if (str[i])
			res[ires++] = str[i++];
	}
	return (res[ires] = '\0', res);
}

int main()
{
	char *str = ft_strdup("TEST=jeteste\"ma fontcion\"");
	char *content = get_content(str);
	printf("avant : %s\n", str);
	rm_quote(&str);
	printf("apres : %s\n", content);
	free(str);
}