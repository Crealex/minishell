/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:30:00 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/22 15:10:30 by dvauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

//utils
void	freesplit(char **str);
void    update_quote(int *in_single, int *in_double, int *i, char *prompt);

//parsing
int		check_builtins(char **prompt);
int		is_pipe(char *str);
int		double_single_quote(const char *s, int i);
int		ft_nb_row(char const *s, char c);
char	**ft_splitpipe(char const *s, char c);
int 	parsing(char *str, char ***env);

//builtins
char	**ft_unset(char ***env, char **prompt, int n);
void	ft_env(char **env);
void	ft_exit(char *str_prompt, char *str, char **prompt, char ***env);

#endif
