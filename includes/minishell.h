/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvauthey <dvauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:30:00 by atomasi           #+#    #+#             */
/*   Updated: 2025/03/07 17:08:47 by dvauthey         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct	s_prompt_info
{
	int		is_pipe;
	int		*fd_in;
	int		*fd_out;
	int		temp_fdin;
	int		temp_fdout;
	int		fd_history;
	int		pos_pipe;
	int		pipe_len;
	int		*redirection;
	char	*str_prt;
	// char	*prt_raw;
	char 	**pipe;
	char	**prompt;
	char	**env;
}			t_prompt_info;

typedef struct s_str
{
	char	*str;
	int		i;
}		t_str;

void	get_history(int fd);
void	manage_history(char *str, int fd);
int		parsing(t_prompt_info *data);
// builtins
void	ft_echo(char *str, t_prompt_info *data);
void	ft_exit(t_prompt_info *data);
void	freesplit(char **str);
void	ft_cd(char **prompt, char ***env);
void	ft_pwd(char **prompt);
int		len_double_tab(char **tab);
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
void	*ft_freesplit(char **res, int j);
char	*ft_getenv(char *var, char **env);
void	cleanup(t_prompt_info *data, int redirect);
int		ft_isspace(int c);
void	print_err(char *s1, char *s2, char *s3);
int		only_space(char **prompt);
char	*char_strjoin(char *str, char c);
//quote
int		len_wquote(char *str);
char	*rm_quote(char *str);
int		is_quote(char *str);
int		update_quote(int *in_single, int *in_double, int *i, char *prompt);
char	*rm_cons_quote(char *str);
//parsing
char	*handle_dollars(char *prompt, char **env);
char	*add_env(char *prompt, int *i, t_str *res, char **all_env);
char	*better_strjoin(char const *s1, char const *s2, char *prompt, int iprompt);
void	init_fd(int *i, int *start, int *end);
void	init_two(int *i, int *j);
void	len_file(char *str, int i, int *start, int *end);
char	*filename(char *str, int i);
char	*del_rd(char *str, int *len, int *index);
int		heredoc(char **str, int i, int *fd, t_prompt_info *data);
char	*parse_heredoc(char *line, t_prompt_info *data);
int		error(char *str, int *i, char *c, char *c1);
void	double_quote(char s, char c, int *i, int *is_double);
int		error_out(char *str, int i);
int		space_around(char **str, char c);
int		get_in_fd(char **str, int fd, t_prompt_info *data);
void	len_file_out(char *str, int i, int *start, int *end);
int		get_out_fd(char **str, int fd, t_prompt_info *data);
int		redirection(t_prompt_info *data, char **str, int i);
int		check_builtins(char **prompt);
int		check_validity(char *cmd, int tok);
int		is_pipe(char **str);
int		handle_pipe(t_prompt_info *data);
char	**dollar_pipe(char **pipe_prompt, t_prompt_info *data);
char	*add_space(char *str, int i, int is_double);
int		ft_nb_row(char const *s, char c);
char	**ft_splitpipe(char const *s, char c);
int		is_valid_cmd(char *str, t_prompt_info *data);
int		check_valid_builtins(char *cmd);
char	**get_all_path();
void	make_redirect(t_prompt_info *data);
void	end_redirect(t_prompt_info *data, int redirect);
char	*expansion(char *str, t_prompt_info *data);
int		handle_quote(t_prompt_info *data);
int		valid_token_cmd(t_prompt_info *data);
// execution
int		extern_exec(t_prompt_info *data);
int		is_child(int status);
int		exec_no_pipe(t_prompt_info *data);
int		exec_pipe(t_prompt_info *data);
int		last_step(char **str, t_prompt_info *data);
//split wquote
char	**split_wquote(char const *s, char c);
int		ft_nb_row(char const *s, char c);
int		double_single_quote(const char *s, int i);
//signal
void	signal_handler(void);


#endif
