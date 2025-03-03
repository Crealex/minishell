/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 20:20:51 by alexandre         #+#    #+#             */
/*   Updated: 2025/03/03 15:06:37 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>

char	*rm_all_quote(char *str)
{
	int     i;
	int     ires;
	char    *res;
	int     quote[2];

	i = 0;
	ires = 0;
	res = malloc(sizeof(char) * (len_wquote(str) + 1));
	if (!res)
		return (NULL);
	quote[0] = 0;
	quote[1] = 0;
	while (str[i])
	{
		while ((str[i] == '\'' && !quote[1]) || (str[i] == '\"' && !quote[0]))
			if (!update_quote(&quote[0], &quote[1], &i, str))
				break ;
		if (str[i])
			res[ires++] = str[i++];
	}
	res[ires] = '\0';
	if (str)
		free(str);
	return (res);
}

int	handle_quote(t_prompt_info *data)
{
	int i;

	i = 0;
	while (data->prompt[i])
	{
		data->prompt[i] = rm_all_quote(data->prompt[i]);
		if (!data->prompt[i])
		{
			ft_freesplit(data->prompt, i);
			return (0);
		}
		i++;
	}
	data->str_prt = rm_all_quote(data->str_prt);
	if (!data->str_prt)
		return (0);
	return (1);
}

// int main()
// {
//     int isread;
//     char *buffer;

//     isread = 1;
//     buffer = malloc(sizeof(char) * 1000);
//     while (isread > 0)
//     {
//         isread = read(0, buffer, 1000);
//         buffer[isread] = '\0';
//         if (buffer && ft_strlen(buffer) > 0)
//         {
//             printf("in conditoin\n");
//             buffer = rm_all_quote(buffer);
//             if (!buffer)
//                 return (1);
//             printf("res : %s\n", buffer);
//         }
//     }
//     free(buffer);
// }
