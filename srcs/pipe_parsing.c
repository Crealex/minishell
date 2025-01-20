/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:35:45 by dvauthey          #+#    #+#             */
/*   Updated: 2025/01/20 14:55:49 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int exist_closing(char *prompt, char c, int i)
{
    static int in_quote = 0;

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

void    update_quote(int *in_single, int *in_double, int *i, char *prompt)
{
    int quote_status;

    if (prompt[*i] == '\'' && !*in_double)
    {
        quote_status = exist_closing(prompt, '\'', *i);
        if (quote_status == 0)
            return ;
        else if (quote_status == 1)
            *in_single = 1;
        else if (quote_status == 2)
            *in_single = 0;
        (*i)++;
    }
    else if (prompt[*i] == '\"' && !*in_single)
    {
        quote_status = exist_closing(prompt, '\"', *i);
        if (quote_status == 0)
            return ;
        else if (quote_status == 1)
            *in_double = 1;
        else if (quote_status == 2)
            *in_double = 0;
        (*i)++;
    }
}

int     *init(int **quote, int *i, int *in_pipe)
{
    *quote[0] = 0;
    *quote[1] = 0;
    *i = 0;
    *in_pipe = 0;
}

 int	*pipe_parsing(char *prompt)
 {
	int	quote[2];
	int	i;
	int	in_pipe;
	int	pipe[2];
	int	prpt;

	quote[0] = 0;
	quote[1] = 0;
	i = 0;
	in_pipe = 0;
	prpt = 0;
	while (prompt[i])
	{
		while (prompt[i] == ' ')
			i++;
		prpt++;
		update_quote(&quote[0], &quote[1], &i, prompt);
		if (!quote[0] && !quote[1])
        {
			if (prompt[i] == '|')
            {
				if (!in_pipe)
				{
					in_pipe = 1;
					pipe[0] = prpt;
				}
                else
                    pipe[1] = prpt;
            }
        }
		i++;
	}
    return (pipe);
 }
