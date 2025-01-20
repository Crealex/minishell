/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:30:00 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/20 14:59:51 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "colors.h"
# include <stdio.h>
# include "../libft/libft.h"
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

int		parsing(char *str);
void	ft_echo(char **prompt);
void    ft_exit(char *str_prompt, char *str, char **prompt);
char 	*parse_prompt(char **prompt, int s);
char *better_join(char *s1, char *s2, char *c);
int	count_occurence(char *str, char c);
//handle dollars
//char *handle_dollar(char *str, char *c);
char *check_dollars(char *prompt);
void	provisory_start_echo(char *str);
void	freesplit(char **str);


#endif
