/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xxx_for_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:09:53 by alexandre         #+#    #+#             */
/*   Updated: 2025/02/04 16:27:59 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <signal.h>
#include <sys/signal.h>

void	sigint_handler(int signal)
{
	if (signal == SIGINT)
		printf("Intercepted SIGINT\n");
}

int main()
{
	//struct sigaction act;

	//ft_bzero(&act, sizeof(act));
	//act.sa_handler = sigint_handler;
	//sigaction(SIGINT, &act, NULL);

	while (1)
	{
		usleep(5000);
	}
}