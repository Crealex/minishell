/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 12:08:37 by atomasi           #+#    #+#             */
/*   Updated: 2025/03/05 11:16:30 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


static int	exist_closing(char *prompt, char c, int i)
{
	static int	in_quote = 0;

	if (in_quote == 1)
	{
		in_quote = 0;
		return (2);
	}
	else if (in_quote == 0)
	{
		while (prompt[i])
		{
			i++;
			if (prompt[i] == c)
			{
				in_quote++;
				return (1);
			}
		}
	}
	return (0);
}

static int	up_quote(int *in_single, int *in_double, int *i, char *prompt)
{
	int	quote_status;

	if (prompt[*i] == '\'' && !*in_double)
	{
		quote_status = exist_closing(prompt, '\'', *i);
		if (quote_status == 0)
			return (0);
		else if (quote_status == 1)
			*in_single = 1;
		else if (quote_status == 2)
			*in_single = 0;
	}
	else if (prompt[*i] == '\"' && !*in_single)
	{
		quote_status = exist_closing(prompt, '\"', *i);
		if (quote_status == 0)
			return (0);
		else if (quote_status == 1)
			*in_double = 1;
		else if (quote_status == 2)
			*in_double = 0;
	}
	return (1);
}

int chckquote(char *str, int i, int *tested, int quote[2])
{
	if (((str[i] == '\'' && !quote[1]) || (str[i] == '\"' && !quote[0])) && *tested == 0)
		return (0);
	*tested = 0;
	return (1);
}

char *expansion(char *str, t_prompt_info *data)
{
	int		i;
	int		quote[2];
	t_str	res;
	//int tested;

	i = 0;
	quote[0] = 0;
	quote[1] = 0;
	res.i = 0;
	//tested = 1;
	res.str = ft_calloc((ft_strlen(str) + 1), sizeof(char));
	if (!res.str)
		return (NULL);
	while (str[i])
	{
		while ((str[i] == '\'' && !quote[1]) || (str[i] == '\"' && !quote[0]))
		{
			up_quote(&quote[0], &quote[1], &i, str);
			//printf("str[i] in conditon : %c quote[0] : %d, i : %d\n", str[i], quote[0], i);
			res.str[res.i++] = str[i++];
			//tested = 1;
		}
		if (str[i] == '$' && !quote[0])
			res.str = add_env(str, &i, &res, data->env);
		//printf("str[i] : %c, i : %d, tested : %d\n", str[i], i, tested);
		if (str[i] && (str[i] != '$' || quote[0]) && !(str[i] == '\'' && !quote[1]))
		{
			res.str[res.i++] = str[i++];
		}
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
