/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:51:40 by jcoquard          #+#    #+#             */
/*   Updated: 2023/12/04 15:54:18 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <signal.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdarg.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <fcntl.h>
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

# define ERR_PIPE "patate: syntax error near unexpected token '|'\n"
# define ERR_OPTION "patate: this option isn't managed\n"
# define ERR_SQUOTE "patate: ' isn't closed\n"
# define ERR_DQUOTE "patate: \" isn't closed\n"
# define ERR_NEWLINE "patate: syntax error near unexpected token 'newline'\n"
# define ERR_MALLOC "patate: malloc failed\n"
# define ERR_DUP2 "patate: dup2 failed\n"

# define ERR_OPIPE "patate: couldn't open the pipe\n"
# define ERR_FORK "patate: couldn't fork\n"
# define ERR_WAITPID "patate: waitpid failed\n"
# define ERR_CD1 "patate: ft_cd: string not in pwd:"
# define ERR_CD2 "patate: ft_cd: too many arguments\n"
# define ERR_CD3 "patate: ft_cd: Don't know the way home :'(\n"

# define ERR_LOST "patate: sorry but you're lost\n"

extern int	g_rvalue;

//echo $"HOME"
//exit | exit
//parsing expand identique a export et unset donc a refaire

typedef struct s_quote
{
	int	s;
	int	d;
}	t_quote;

typedef enum e_redir
{
	NONE,
	HEREDOC,
	INFILE,
	OUTFILE,
	OUTAPPEND
}	t_redir;

typedef struct s_cmd
{
	unsigned int	id;
	pid_t			pid;
	char			*cmd;
	char			*exec;
	char			**args;
	int				nb_args;
	int				built_in;
	t_redir			redir_in;
	int				infile;
	int				outfile;
	int				pipe[2];
}	t_cmd;

typedef struct s_line
{
	char			*line;
	t_cmd			*cmds;
	unsigned int	nb_cmds;
	bool			heredocs;
}	t_line;

typedef struct s_data
{
	char	**env;
	t_line	prompt;
}	t_data;

/*     process     */
int			process(t_data *shell);
int			set_rval(int val, char *error);

/*     signals     */
void		prompt_sigint(int sig);
void		heredoc_sigint(int sig);
void		exec_handler(int sig);
void		heredoc_signals(void);
void		unplug_signals(void);
void		exec_signals(void);
void		prompt_signals(void);

/*     parsing     */
int			pars_line(char *line);
int			manage_quote(char c, t_quote *quote);
void		free_dtab(char **tab);
char		get_pos(char c);
char		*ft_addchar(char *str, char c);
int			striswspace(char *str);
int			is_emptypipe(char *line);
int			error_syntax(char *str, char c);
int			is_bracketvalid(char *str, char c, int *tmp);
char		*expand(t_data *shell, char *line);
int			pars_redir(t_cmd *cmd);
int			pars_heredoc(t_data *shell, t_cmd *cmd);

/*     environment     */
int			init_env(t_data *shell, char **envp);
void		clear_env(t_data *shell);
char		*get_env_var(t_data *shell, char *var);
int			del_var(t_data *shell, char *var);
int			len_env(char **env);
char		*new_env_var(char *var, char *value, char *old_value);
int			add_var(t_data *shell, char *var, char *value);
int			is_var(char **env, char *var);

/*     execution     */
void		ft_close(int *fd);
void		close_cmd(t_cmd *cmd);
void		wait_heredoc(pid_t pid);
char		*get_cmd(t_data *shell, char *cmd);
int			exec(t_data *shell, t_cmd *cmd);
int			exec_builtins(t_data *shell, t_cmd *cmd, int pid);
void		clear_proc(t_data *shell, int pid);

/*     utils     */
int			splitcmds(t_data *shell, char *line);
void		free_cmds(t_data *shell);
int			splitargs(t_cmd *cmd, char *line);
size_t		strcpy_neg(char *dst, const char *src, size_t size);
long long	ft_atoll(const char *str);
char		*geteof(char *str, int *is_quote);
char		*strpos(char *str);
void		put_sortedstr(char **strs, int start, int end);

/*     builtin     */
int			ft_exit(t_data *shell, t_cmd *cmd, char **arg, int pid);
int			ft_pwd(t_data *shell, int pid);
int			ft_echo(t_data *shell, t_cmd *cmd, int pid);
void		ft_env(t_data *shell, int pid);
int			ft_unset(t_data *shell, t_cmd *cmd, int pid);
int			ft_cd(t_data *shell, t_cmd *cmd, int pid);
int			ft_export(t_data *shell, t_cmd *cmd, int pid);

//pour les exports le nom devariable commence par _ ou 
//alphachar puis on peut mettre desn ombres
//faire l'expand avant les redirections !!
//si ' pas interpreter $ si " interpreter
//heredocs lancé en premier puis commandes
//separer au pipe ; en bonus
//si eof heredocs entre "" pas interpreter $ sinon interpreter
//si << et commande la commande s'execute peut importe l'ordre d'apelle
//penser au char spe : " ' * $ | <<
//si "" bien copier tout le contenu
//si '%2 = 1 || "%2 = 1 planter (ne pas conter le contenue entre guillemet)
//<< si 0 mot apres planter (le mot peut etre une commande)
//retirer tout les espaces n'etant pas entre guillemet
//$ a gerer meme entre quote ($$ pas a gerer)
//utiliser getenv() pour obtenir les variable d'environement
// < > redirection !!
// export si export test=test = pas cole resultat vide
//cd use chdir();
//pwd use getcwd(NULL, 0);
//echo refaire printf en dprintf avec generation de toute la ligne avant printf
//trouver les binaires avec acces (penser au ./ ou commande)
//cd use chdir (cas a gerer si rien mi faire chdir(getenv("HOME"));)
//cd ne marche pas dans des pipes (car le cd ce fait dans le child mais executer
//quand meme)
//message d'erreur pour cd si HOME unset
//guillemets et quotes, ne pas conter les quote entre guillemet et inversement
//limite 3333 pipe !!
//$? a remplacer en valeur de retour pas une variable

#endif