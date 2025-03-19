/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:28:28 by alexandre         #+#    #+#             */
/*   Updated: 2025/03/19 11:41:59 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
}

void	ign_sig(void)
{
	struct sigaction	ign;

	ft_bzero(&ign, sizeof(ign));
	ign.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &ign, NULL);
	sigaction(SIGINT, &ign, NULL);
}

static void	reset(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", 1);
}

void	reset_sig(void)
{
	struct sigaction	res;

	ft_bzero(&res, sizeof(res));
	res.sa_handler = &reset;
	sigaction(SIGQUIT, &res, NULL);
	sigaction(SIGINT, &res, NULL);
}

void	signal_handler(void)
{
	struct sigaction	act;
	struct sigaction	ign;

	ft_bzero(&act, sizeof(act));
	ft_bzero(&ign, sizeof(ign));
	act.sa_handler = &which_sig;
	ign.sa_handler = SIG_IGN;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &ign, NULL);
}
