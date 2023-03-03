/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:02:46 by egeorgel          #+#    #+#             */
/*   Updated: 2023/03/03 21:58:19 by egeorgel         ###   ########.fr       */
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

typedef struct s_data
{
	char	**envp;
	char	**errlst;
	char	*prompt;
	t_list	*lst;
	int		out_fd;
	int		in_fd;
	pid_t	pid;
}	t_data;

void	get_redirection_out(t_data *data);
char	*ft_startincharset(char *str, char *charset);
void	prompt(t_data *data);
void	error(int err, char *input, t_data *data);
void	get_errlst(t_data *data);
char	**sep_input(char *input);
int		*realloc_fd(int new_fd, int	*fds);
int		last_fd(int *fds);
void	ft_strrem(char *str, char *rem);
void	ft_rem_double_space(char *str, char *sep);
t_list	*sep_token(char *str, t_data *data);
void	remove_from_list(t_list **lst, t_list *rem);
bool	set_to_opposite(bool b);
#endif