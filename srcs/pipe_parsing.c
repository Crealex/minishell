/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:35:45 by dvauthey          #+#    #+#             */
/*   Updated: 2025/01/21 11:53:11 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_nb(const char *s, char c, int i, int *start)
{
    while (s[i] && s[i] == c)
        i++;
    *start = i;
    while (s[i] && s[i] != c && s[i] != '\'' && s[i] != '\"')
    {
        i++;
    }
	if (s[i] && s[i] != c)
		i = double_single_quote(s, i);
    while (s[i] && s[i] != c)
        i++;
    return (i);
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
    int		i;
    int		j;
    int		start;
    char	**result;

    i = 0;
    j = 0;
    start = 0;
    result = malloc((ft_nb_row(s, c) + 1) * sizeof(char *));
    if (result == NULL)
        return (NULL);
    while (s[i])
    {
        i = ft_nb(s, c, i, &start);
        if (start != i)
        {
            result[j] = ft_strinrow(s, start, i);
            if (!result[j])
                return (ft_freesplit(result, j));
            j++;
        }
    }
    result[j] = NULL;
    return (result);
}

int is_pipe()