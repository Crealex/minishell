/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:35:45 by dvauthey          #+#    #+#             */
/*   Updated: 2025/01/21 16:49:20 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int exist_closing(char *prompt, char c, int i)
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

static int	ft_nb(const char *s, char c, int *i, int *start)
{
    int j;

    j = 0;
    while (s[*i] && (s[*i] == c || s[*i] == ' '))
        (*i)++;
    *start = *i;
    while (s[*i] && s[*i] != c && s[*i] != '\'' && s[*i] != '\"')
    {
        (*i)++;
    }
	if (s[*i] && s[*i] != c)
		*i = double_single_quote(s, *i);
    while (s[*i] && s[*i] != c)
        (*i)++;
    if (*i > 0 && s[*i - 1] == ' ')
        j++;
    while (*i > 0 && s[*i] == ' ')
        j++;
    return (j);
}	

static char	*ft_strinrow(char const *s, int start, int end)
{
    char	*row;
    int		i;

    i = 0;
    row = malloc((end - start + 1) * sizeof(char));
    if (row == NULL)
        return (NULL);
    while (i < (end - start))
    {
        row[i] = s[start + i];
        i++;
    }
    row[i] = '\0';
    return (row);
}

static void	*ft_freesplit(char **res, int j)
{
    int	i;

    i = 0;
    while (i < j)
    {
        free(res[i]);
        i++;
    }
    free(res);
    return (NULL);
}

char	**ft_splitpipe(char const *s, char c)
{
    int		index[2];
    int		start_end[2];
    char	**result;

    index[0] = 0;
    index[1] = 0;
    start_end[0] = 0;
    result = malloc((ft_nb_row(s, c) + 1) * sizeof(char *));
    if (result == NULL)
        return (NULL);
    while (s[index[0]])
    {
        start_end[1] = ft_nb(s, c, &index[0], &start_end[0]);
        if (start_end[0] != index[0])
        {
            result[index[1]] = ft_strinrow(s, start_end[0], index[0]);
            if (!result[index[1]])
                return (ft_freesplit(result, index[1]));
            index[1]++;
        }
        else
            break ;
    }
    result[index[1]] = NULL;
    return (result);
}
