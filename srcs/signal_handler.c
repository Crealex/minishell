/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:28:28 by alexandre         #+#    #+#             */
/*   Updated: 2025/02/26 11:34:38 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>


static void	which_sig(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		if (is_child(-1) == 0)
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
	//utiliser les fonctions readline pour revenir au prompt
}

void	signal_handler()
{
	struct sigaction act;
	struct sigaction ign;

	ft_bzero(&act, sizeof(act));
	ft_bzero(&ign, sizeof(ign));
	act.sa_handler = &which_sig;
	ign.sa_handler = SIG_IGN;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT,&ign,NULL);
}
