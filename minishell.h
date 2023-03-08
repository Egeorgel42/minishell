/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuzmin <vkuzmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:02:46 by egeorgel          #+#    #+#             */
/*   Updated: 2023/03/08 19:54:10 by vkuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>

typedef enum e_err{
	ERRNO,
	ERR_CMD,
	ERR_FD,
	ERR_FLAG,
	ERR_PARSING,
	ERR_ARGS,
	ERR_UNSUPORTED,
	ERR_QUOTES,
	ERR_EMPTY,
	ERR_MAX
}	t_err;

typedef struct s_env
{
	char			*pref;
	char			*string;
	char			*full_string;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	char	**envp;
	char	**path;
	char	**errlst;
	char	*prompt;
	t_list	*lst;
	t_env	*env;
	int		out_fd;
	int		in_fd;
	pid_t	pid;
}	t_data;

void	error(int err, char *input, char *token, t_data *data);

bool	is_flaged(char **str);
void	mini_pwd(char **str, t_data *data);
void	mini_env(char **str, t_data *data);
void	check_pwd(char *str);
void	mini_echo(char **str, t_data *data);
void	mini_export(char **str, t_env **env, t_data *data);
void	create_env(char **envp, t_env **env);
t_env	*create_node(char *str);
void	mini_unset(char **str, t_env **env, t_data *data);
char	*delete_slash(char *str);
void	change_oldpwd(char *old, t_env **env);

bool	callstructure(t_data *data);
void	get_redirection_out(t_data *data);
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
#endif