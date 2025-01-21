/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:42:07 by dvauthey          #+#    #+#             */
/*   Updated: 2025/01/21 17:25:39 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int is_pipe(char *str)
{
    int i;
    int inquote[2];
	int	empty_pipe;

    i = 0;
    inquote[0] = 0;
    inquote[1] = 0;
	empty_pipe = 0;
    while (str[i])
    {
		update_quote(&inquote[0], &inquote[1], &i, str);
		if (i == 0 && iswtspace(str[i]))

			while (iswtspace(str[i]))
				i++;
		if (!inquote[0] && !inquote[1] && str[i] == '|' )
		{
			if ()
		} 
    }
    return (0);
}