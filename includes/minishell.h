/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:30:00 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/22 17:14:48 by atomasi          ###   ########.fr       */
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

int		parsing(char *str, char ***env);
void	ft_echo(char *str);
void	ft_exit(char *str_prompt, char *str, char **prompt);
void	freesplit(char **str);
void	ft_cd(char **prompt);
void	ft_pwd(char **prompt);
void	ft_export(char **prompt, char ***env);
//fonction utils not use
char	*better_join(char *s1, char *s2, char *c);
int		count_occurence(char *str, char c);
//utils
int		update_exit_code(int param);
//parsing
char	*handle_dollars(char *prompt);
void	update_quote(int *in_single, int *in_double, int *i, char *prompt);
char	*better_strjoin(char const *s1, char const *s2, char *prompt, int iprompt);
//split wquote
char	**split_wquote(char const *s, char c);
int		ft_nb_row(char const *s, char c);
int		double_single_quote(const char *s, int i);


#endif
