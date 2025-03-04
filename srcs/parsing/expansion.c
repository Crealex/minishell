/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 12:08:37 by atomasi           #+#    #+#             */
/*   Updated: 2025/03/04 10:09:08 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int chckquote(char *str, int i, int *tested)
{
	if (str[i] == '\'' && *tested == 0)
		return (0);
	*tested = 0;
	return (1);
}

char *expansion(char *str, t_prompt_info *data)
{
	int		i;
	int		quote[2];
	t_str	res;
	int tested;

	i = 0;
	quote[0] = 0;
	quote[1] = 0;
	res.i = 0;
	tested = 1;
	res.str = ft_calloc((ft_strlen(str) + 1), sizeof(char));
	if (!res.str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'')
		{
			if (update_quote(&quote[0], &quote[1], &i, str) > 0)
				i--;
			tested = 1;
		}
		else if (str[i] == '$' && !quote[0])
			res.str = add_env(str, &i, &res, data->env);
		if (str[i] && (str[i] != '$' || quote[0]) && chckquote(str, i, &tested))
			res.str[res.i++] = str[i++];
	}
	res.str[res.i] = '\0';
	return (free(str), res.str);
}

	// MAIN DE TEST
	//
// 	int main(int argc, char **argv, char **env)
// 	{
// 	t_prompt_info data;
// 	int isread;

// 	(void)argv;
// 	(void)argc;
// 	isread = 1;
// 	data.env = NULL;
// 	data.env = cpy_double_array(data.env, env);
// 	data.str_prt = ft_calloc(1000, sizeof(char));
// 	while (isread > 0)
// 	{
// 		isread = read(0, data.str_prt, 1000);
// 		data.str_prt[isread] = '\0';
// 		data.str_prt = expansion(data.str_prt ,&data);
// 		if (!data.str_prt)
// 			return (EXIT_FAILURE);
// 		printf("res : %s\n", data.str_prt);
// 	}
// 	free(data.str_prt);
// 	return EXIT_SUCCESS;
// }
