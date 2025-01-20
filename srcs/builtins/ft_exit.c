/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:46:27 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/20 14:48:02 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    ft_exit(char *str_prompt, char *str, char **prompt)
{
    int    i;
    int    value;

    i = 0;
    value = 0;
    if (str_prompt)
    {
        while (ft_isdigit(str_prompt[i]))
            i++;
        if (i == (int)ft_strlen(str_prompt))
            value = ft_atoi(str_prompt);
        else
        {
            write(2, "Minishell: exit: ", 17);
            write(2, str_prompt, ft_strlen(str_prompt));
            write(2, ": numeric argument required\n", 28);
            value = 2;
        }
    }
    free(str);
    freesplit(prompt);
    exit(value);
}