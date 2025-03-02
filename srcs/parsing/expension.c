/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expension.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 12:08:37 by atomasi           #+#    #+#             */
/*   Updated: 2025/03/02 12:17:03 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *expension(t_prompt_info *data)
{
    int     i;
    int     quote[2];
    t_str   res;
    
    i = 0;
    quote[0] = 0;
    quote[1] = 0;
    res.i = 0;
    res.str = ft_calloc((ft_strlen(data->str_prt) + 1), sizeof(char));
    if (!res.str)
        return (NULL);
    while (data->str_prt[i])
    {
        if (data->str_prt[i] == '\'')
            if (update_quote(&quote[0], &quote[1], &i, data->str_prt) > 0)
                i--;
        else if (data->str_prt[i] == '$' && !quote[0])
            res.str = add_env(data->str_prt, &i, &res, data->env);
        if (data->str_prt[i])
            res.str[res.i++] == data->str_prt[i++];
    }
    return (res.str);
}

// MAIN DE TEST
//
int main(int argc, char **argv, char **env)
{
    t_prompt_info data;
    int isread;

    isread = 1;
    data.env = cpy_double_array(data.env, env);
    data.str_prt = ft_calloc(1000, sizeof(char));
    while (isread > 0)
    {
        isread = read(0, data.str_prt, 1000);
        data.str_prt = expension(&data);
        if (!data.str_prt)
            return (EXIT_FAILURE);
        printf("res : %s\n", data.str_prt);
    }
    free(data.str_prt);
    return EXIT_SUCCESS;
}
