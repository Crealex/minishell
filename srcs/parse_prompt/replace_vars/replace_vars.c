/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:16:15 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/17 18:06:20 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int is_closing(char *prompt, char c)
{
	int i;
	static int quote = 0;
	static int even = 0;
	static int last = -1;

	if (quote == 2)
		quote = 0;
	else if (quote == 1)
		quote = 2;
	else if (quote == 0)
	{
		while (prompt[i])
		{
			if (prompt == c)
				even++;
			if (even % 2 == 0 && even != last)
			{
				last = even;
				break ;
			}
			i++;
		}
	}
}

int check_dollars(char *prompt)
{
	int i;
	int ires;
	int in_single;
	int in_double;
	char *res;

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == '\'' || prompt[i] == '\"' && is_closing(prompt, prompt[i]) > 0) // au lieux de me compliquer la vue je pourrai jsute recup le i pour savoir ou j'en suis
		{
			if (prompt[i] == '\'')
				in_single = 1;
			else if (prompt[i] == '\"')
				in_double = 1;
			i++;
		}
		if (prompt[i] == '$' && in_single == 0)
			res = add_env(prompt, &i, &ires, in_double);
		res[ires] = prompt[i];
		ires++;
		i++;
	}
}
