/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:02:46 by egeorgel          #+#    #+#             */
/*   Updated: 2023/03/28 23:47:48 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include "../libs/libft/libft.h"
# include "../libs/readline/include/readline/readline.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <termios.h>

typedef enum e_err{
	ERRNO,
	ERR_CMD,
	ERR_FD,
	ERR_EXP,
	ERR_FLAG,
	ERR_PARSING,
	ERR_ARGS,
	ERR_UNSUPORTED,
	ERR_QUOTES,
	ERR_HOME,
	ERR_OLDPWD,
	ERR_HOME_HIS,
	ERR_EMPTY,
	ERR_START_PWD,
	ERR_MAX
}	t_err;

typedef struct s_env
{
	char			*pref;
	char			*string;
	char			*full_string;
	struct s_env	*next;
}	t_env;

typedef struct s_pidlst
{
	pid_t			pid;
	struct s_pidlst	*next;
}	t_pidlst;

typedef struct s_data
{
	char		**envp;
	char		**path;
	char		**errlst;
	char		*prompt;
	char		*pwd;
	char		*last_history;
	t_list		*lst;
	t_env		*env;
	int			history_fd;
	int			out_fd;
	int			in_fd;
	int			pipe_fd;
	t_pidlst	*pidlst;
}	t_data;

void	error_exit(int err, char *input, char *token, t_data *data);

bool	is_flaged(char **str);
void	mini_pwd(char **str, t_data *data);
void	mini_env(char **str, t_data *data);
void	mini_echo(char **str, t_data *data);
void	mini_export(char **str, t_data *data);
void	create_env(char **envp, t_env **env);
t_env	*create_node(char *str);
void	mini_unset(t_data *data, char **str);
char	*delete_slash(char *str);
void	mini_cd(t_data *data, char **input);
char	*add_slash(char *str);
void	replace_charset_to_c(char *str, char *charset, char c);
void	create_pwd(t_env **env);
void	going_back(t_env **env);

bool	callstructure(t_data *data);
bool	get_redirection_out(t_data *data);
void	remove_quotes(t_data *data);
void	prompt(t_data *data);
void	get_errlst(t_data *data);
void	ft_rem_double_space(char *str, char *sep);
t_list	*sep_token(char *str, t_data *data);
void	remove_from_list(t_list **lst, t_list *rem);
bool	set_to_opposite(bool b);
void	rem_until_rem(t_list **lst, t_list *rem);
void	update_envp(t_data *data);
char	**get_cmd(t_data *data);
void	get_path(t_data *data);
void	add_pid(pid_t pid, t_data *data);
pid_t	last_pid(t_data *data);
void	wait_pids(t_data *data);
void	parent_cmd(t_data *data);
bool	is_pipe(t_data *data);
void	clear_pidlst(t_data *data);
void	signal_handler(int sig);
void	mini_exit(void);
void	replace_in_str(char **str, char *replace, int start, int end);
bool	get_env(t_data *data);
void	ft_exit(void);

//pipes fonctions
void	cmd_process(char **cmd, t_data *data, bool last);
bool	inbuilts(char **cmd, t_data *data);
void	excve(char **cmd, t_data *data);
void	get_history(t_data *data);
void	save_history(t_data *data);
void	error(int err, char *input, char *token, t_data *data);
char	*get_str_env(t_data *data, char *env);
t_env	*get_in_env(t_data *data, char *env);
char	*get_pwd(t_data *data, char *dir);
t_env	*almost_last_env(t_data *data);
void	start_pwd(t_data *data);
t_env	*get_prev_in_env(t_data *data, char *env);
#endif