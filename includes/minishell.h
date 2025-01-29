/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:30:00 by atomasi           #+#    #+#             */
/*   Updated: 2025/01/29 14:37:25 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "colors.h"
# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

void	get_history(int fd);
void	manage_history(char *str, int fd);
int		parsing(char *str, char ***env);
// builtins
void	ft_echo(char *str);
void	ft_exit(char *str_prompt, char *str, char **prompt, char ***env);
void	freesplit(char **str);
void	ft_cd(char **prompt);
void	ft_pwd(char **prompt);
void	ft_export(char **prompt, char ***env);
int		var_exist(char *str, char **env);
void	modify_var(char *str, char ***env);
void	cat_var(char *str, char ***env);
char	*get_name(char *str);
char	*get_content(char *str);
char	*remove_plus(char *str);
void	display_sort(char **env);
void	ft_env(char **env);
char	**ft_unset(char ***env, char **prompt, int n);
//fonction utils not use
char	*better_join(char *s1, char *s2, char *c);
int		count_occurence(char *str, char c);
//utils
int		update_exit_code(int param);
char	**cpy_double_array(char **cpy, char **src);
//quote
int		len_wquote(char *str);
void	rm_quote(char **str);
int		is_quote(char *str);
void	update_quote(int *in_single, int *in_double, int *i, char *prompt);
//parsing
char	*handle_dollars(char *prompt);
char	*better_strjoin(char const *s1, char const *s2, char *prompt, int iprompt);
int		check_builtins(char **prompt);
int		is_pipe(char *str);
int		ft_nb_row(char const *s, char c);
char	**ft_splitpipe(char const *s, char c);
//split wquote
char	**split_wquote(char const *s, char c);
int		ft_nb_row(char const *s, char c);
int		double_single_quote(const char *s, int i);


#endif
