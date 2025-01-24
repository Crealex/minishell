/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:57:09 by alexandre         #+#    #+#             */
/*   Updated: 2025/01/24 16:19:40 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
