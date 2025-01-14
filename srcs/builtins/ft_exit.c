/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:50:04 by dvauthey          #+#    #+#             */
/*   Updated: 2025/01/14 18:07:55 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//ATTENTION : GESTION ERROR
void	ft_exit(char *str)
{
	int	i;
	int	value;

	i = 0;
	value = 0;
	if (str)
	{
		while (ft_isdigit(str[i]))
			i++;
		if (i == (int)ft_strlen(str))
			value = ft_atoi(str);
	}
	exit(value);
}