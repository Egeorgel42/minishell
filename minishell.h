/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:02:46 by egeorgel          #+#    #+#             */
/*   Updated: 2023/03/03 22:51:01 by egeorgel         ###   ########.fr       */
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
	ERR_EXC,
	ERR_EMPTYREDIRECTION,
	ERR_CMD,
	ERR_FD,
	ERR_PARSING,
	ERR_UNSUPORTED,
	ERR_QUOTES,
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
	char	**errlst;
	char	*prompt;
	t_list	*lst;
	t_env	*env;
	int		out_fd;
	int		in_fd;
	pid_t	pid;
}	t_data;

void	error(int err, char *input, t_data *data);

char	*cutspaces(char *str);
void	mini_pwd(char *str);
void	mini_env(char *str, t_env **env);
void	check_pwd(char *str);
void	mini_echo(char *str);
void	mini_export(char *str, t_env **env);
void	create_list(char **envp, t_env **head);

char	*full_string(char *str);
char	*find_pref(char *str);
char	*find_string(char *str);
t_env	*create_node(char *str);
void	mini_unset(char *str, t_env **env);

void	get_redirection_out(t_data *data);
void	prompt(t_data *data);
void	get_errlst(t_data *data);
void	ft_strrem(char *str, char *rem);
void	ft_rem_double_space(char *str, char *sep);
t_list	*sep_token(char *str, t_data *data);
void	remove_from_list(t_list **lst, t_list *rem);
bool	set_to_opposite(bool b);
#endif