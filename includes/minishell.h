/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:02:46 by egeorgel          #+#    #+#             */
/*   Updated: 2023/06/09 00:51:45 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <termios.h>
# include <stdio.h>
# include "../libs/libft/libft.h"
# include "../libs/readline/include/readline/readline.h"
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <limits.h>

typedef enum e_err{
	ERRNO,
	ERR_REDIR,
	ERR_CMD,
	ERR_FD,
	ERR_DIR,
	ERR_NOT_DIR,
	ERR_EXP,
	ERR_FLAG,
	ERR_PERM,
	ERR_PARSING,
	ERR_ARGS,
	ERR_ARGS_NBR,
	ERR_UNSUPORTED,
	ERR_EXIT,
	ERR_QUOTES,
	ERR_HOME,
	ERR_HOME_CD,
	ERR_OLDPWD,
	ERR_HOME_HIS,
	ERR_EMPTY,
	ERR_START_PWD,
	ERR_MAX
}	t_err;

typedef struct s_sig
{
	bool			heredoc;
	int				status;
	pid_t			pid;
}	t_sig;

typedef struct s_env
{
	char			*pref;
	char			*string;
	char			*full_string;
	bool			is_equal;
	struct s_env	*next;
}	t_env;

typedef struct s_pidlst
{
	pid_t			pid;
	struct s_pidlst	*next;
}	t_pidlst;

typedef struct s_data
{
	bool				get_status;
	bool				print_path;
	int					status;
	int					cmd_status;
	char				**envp;
	char				**path;
	char				**errlst;
	char				*prompt;
	char				*pwd;
	char				*last_history;
	t_list				*lst;
	t_env				*env;
	int					history_fd;
	int					out_fd;
	int					in_fd;
	int					pipe_fd;
	t_pidlst			*pidlst;
	struct termios		attr;
	struct termios		saved;
	struct sigaction	act;
}	t_data;

//sig
void		sigint(int sig);
void		sigquit(int sig);
void		empty_sigint(int sig);
void		sigint_here(int sig);
void		start_attr(t_data *data);
void		signal_messages(t_data *data, int sig);

//builtins
bool		inbuilts(char **cmd, t_data *data, bool pipe);
bool		is_flaged(char **str);

void		mini_pwd(t_data *data);
void		mini_env(char **str, t_data *data);
void		mini_echo(t_data *data, char **str);
void		mini_export(char **str, t_data *data);
void		mini_exit(t_data *data, char **str, bool pipe);
void		mini_unset(t_data *data, char **str);
void		mini_cd(t_data *data, char **input);
void		cd_oldpwd(t_data *data, char **input);
void		cd_fction(t_data *data, char *input);

char		*get_pwd(t_data *data, char *dir);
void		start_pwd(t_data *data);

//env
void		create_env(char **envp, t_env **env);
t_env		*create_node(char *str);
void		start_env(t_data *data);
void		update_envp(t_data *data);
bool		get_env(t_data *data);
bool		developp_env(t_data *data, char **str);
void		parse_env(char **env_str, int i, bool *quotes);
char		*get_str_env(t_data *data, char *env);
t_env		*get_in_env(t_data *data, char *env);
t_env		*almost_last_env(t_data *data);
t_env		*get_prev_in_env(t_data *data, char *env);
int			env_size(t_env *env);
int			exit_status(t_data *data, char **str, int i);

//piping
char		*access_p(t_data *data);
int			get_redirection_out(t_data *data);
bool		heredoc(t_data *data, char *sep);
void		callstructure(t_data *data);
void		wait_pids(t_data *data);
void		parent_cmd(t_data *data);
bool		is_pipe(t_data *data);
bool		cmd_process(char **cmd, t_data *data);
void		kill_all(t_data *data);
void		excve(char **cmd, t_data *data);

//parsing
t_list		*sep_token(char *str, t_data *data, bool *quotes);
bool		check_sep_token(t_list	*lst, t_data *data);
int			token_end(char *str, bool *quotes, int j);
bool		invalid_token(t_data *data, t_list *lst, int i);
void		sep_loop(char *str, int *j, bool *quotes);
bool		check_first_pipe(t_data *data, char *str, bool *quotes);
char		**get_cmd(t_data *data);
void		get_path(t_data *data);
void		get_history(t_data *data);
void		save_history(t_data *data);

//err
void		get_errlst(t_data *data);
void		error(int err, char *input, char *token, t_data *data);
void		error_exit(int err, char *input, char *token, t_data *data);

//utils
char		*delete_slash(char *str);
char		*add_slash(char *str);
void		replace_charset_to_c(char *str, char *charset, char c);
void		remove_quotes(t_data *data);
void		ft_rem_double_space(char *str, char *sep);
void		ft_rem_double_space_quotes(char *str, char *sep);
void		replace_in_str(char **str, char *replace, int start, int end);
bool		set_to_opposite(bool b);
void		sort_and_print(t_data *data, t_env *env);
t_env		*copy_env_list(t_env *head);
bool		empty_pipe(t_list *lst, t_data *data);

void		remove_from_list(t_list **lst, t_list *rem);
void		rem_until_rem(t_list **lst, t_list *rem);

void		add_pid(pid_t pid, t_data *data);
void		clear_pidlst(t_data *data);

#endif