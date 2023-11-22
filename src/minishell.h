/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:51:40 by jcoquard          #+#    #+#             */
/*   Updated: 2023/11/20 13:22:07 by edecoste         ###   ########.fr       */
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

# define PRONPT RED"patate> "END
# define ERR_SYNTAX "patate: syntax error near unexpected token"
# define ERR_SQUOTE "patate: ' isn't closed\n"
# define ERR_DQUOTE "patate: \" isn't closed\n"
# define ERR_PIPE1 "patate: syntax error near unexpected token '|'\n"
# define ERR_PIPE2 "patate: there missing something after '|'\n"
# define ERR_NEWLINE "patate: syntax error near unexpected token 'newline'\n"
# define ERR_MALLOC "patate: malloc failed"
# define ERR_MANAGE "patate: this option isn't managed\n"
# define ERR_PATH "patate: "
# define ERR_CD1 "patate: ft_cd: too many arguments\n"

extern int	g_rvalue;

typedef struct s_quote
{
	int	s;
	int	d;
}	t_quote;

typedef struct s_cmd
{
	char	*cmd;
	char	*exec;
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
}	t_line;

typedef struct s_data
{
	char	**env;
	t_line	prompt;
}	t_data;

/*     parsing     */
int		pars(t_data *shell);
int		pars_redir(t_cmd *cmd);
char	*trim(t_data *shell, t_cmd *cmd, char *line);
int		striswspace(char *str);
int		is_emptybpipe(char *line);
int		manage_quote(char c, t_quote *quote);
int		is_bracketvalid(char *str, char c, int *tmp);
int		error_syntax_too_much(char *str, char c);
int		splitcmds(t_data *prompt, char *line);
void	free_cmds(t_data *shell);
int		splitargs(t_cmd *cmd, char *line);
void	free_dtab(char **tab);
char	*ft_addchar(char *str, char c);
char	*get_varname(char *str);
int		get_len_var(t_data *shell, char *str, int *len);
int		put_var(t_data *shell, char *str, char *res, int *len_var);
size_t	strcpy_neg(char *dst, const char *src, size_t size);
char	get_pos(char c);
void 	strnegorpos(char *str, char symbol);

/*     environment     */
void	clear_env(t_data *shell);
int		init_env(t_data *shell, char **envp);
char	*get_env_var(t_data *shell, char *var);

/*     exec     */
int	exec(t_data *shell, t_cmd *cmd);
char	*get_cmd(t_data *shell, char *cmd);

/*     heredoc     */
void heredoc(int do_expend, char *eof);

/*     signals     */
void	prompt_signals(void);
void	heredoc_signals(void);
void	unplug_signals(void);
void	exec_signals(void);

void	prompt_sigint(int sig);
void	exec_sigint(int sig);
void	exec_sigquit(int sig);
void	heredoc_sigint(int sig);

/*     exit     */
int	ft_exit(t_data *shell, char **arg);

/*     env     */
void	ft_env(t_data *shell);

/*     export     */
void	ft_export(t_data *shell, char **argv, int pid);


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
