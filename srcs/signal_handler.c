/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:28:28 by alexandre         #+#    #+#             */
/*   Updated: 2025/02/05 09:50:32 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


static void	sig_handler(int signal)
{
	//on est censee kill le process en cours avec :
	if (signal == SIGINT)
		printf("ctrl c intercepted!\n");
	//utiliser les fonctions readline pour revenir au prompt
}

void	signal_handler(void)
{
	struct sigaction act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &sig_handler;
	sigaction(SIGINT, &act, NULL);
}