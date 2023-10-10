/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:51:40 by jcoquard          #+#    #+#             */
/*   Updated: 2023/10/06 17:08:34 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
#include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdarg.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"

# define END "\001\033[0m\002"
# define GREY "\001\033[1;30m\002"
# define RED "\001\033[1;31m\002"
# define GREEN "\001\033[1;32m\002"
# define YELLOW "\001\033[1;33m\002"
# define BLUE "\001\033[1;34m\002"
# define PURPLE "\001\033[1;35m\002"
# define CYAN "\001\033[1;36m\002"

# define END "\001\033[0m\002"
# define BOLD "\001\033[1m\002"
# define ITALIC "\001\033[3m\002"
# define UNDERLINE "\001\033[4m\002"
# define DEL_LINE "\001\033[2K\r\002"

# define ERR_SYNTAX "patate: syntax error near unexpected token"
# define ERR_SQUOTE "patate: ' isn't closed\n"
# define ERR_DQUOTE "patate: \" isn't closed\n"
# define ERR_PIPE1 "patate: syntax error near unexpected token '|'\n"
# define ERR_PIPE2 "patate: there missing something after '|'\n"
# define ERR_NEWLINE "patate: syntax error near unexpected token 'newline'\n"
# define ERR_MALLOC "patate: malloc failed"
# define ERR_MANAGE "patate: this option isn't managed\n"

extern int r_value;

typedef struct s_cmd
{
	char	*cmd;
	int		not_valid;
	char	**args;
	int		nb_args;
	int		built_in;
	int		redir;
	int		infile;
	int		outfile;
	int		fd[2];
}	t_cmd;

typedef struct s_line
{
	char			*line;
	unsigned int	nb_cmds;
	t_cmd			*cmds;
	int				heredocs;
} t_line;

typedef struct s_data
{
	char	**env;
	t_line	prompt;
}	t_data;

/*     parsing     */
int 	pars(t_data *shell);
int		ft_striswspace(char *str);
int		is_emptybpipe(char *line);
void 	manage_quote(char c, int *squote, int *dquote);
int		is_bracketvalid(char *str, char c, int *tmp);
int		error_syntax_too_much(char *str, char c);
int		ft_splitcmds(t_data *prompt, char *line);
void	free_cmds(t_data *prompt);

#endif