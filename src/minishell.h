/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:51:40 by jcoquard          #+#    #+#             */
/*   Updated: 2023/10/04 16:07:05 by liurne           ###   ########.fr       */
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
# define ERR_NEWLINE "patate: syntax error near unexpected token 'newline'\n"
# define ERR_MALLOC "patate: malloc failed"


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
//

typedef struct s_cmd
{
	char	*cmd;
	//char	**args;
	t_list	*args;
	int		nb_args;
	int		heredocs;
	char	*d_heredocs;
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
	t_line	line;
}	t_data;

/* -----utils----- */
char	*ft_addchar(char *str, char c);

/* -----pars----- */
int	is_redir(t_cmd *cmd, char *str, char c);
void	free_cmd(t_data *prompt);
int		ft_split_cmd(t_data *prompt, char *line);
int		pars(t_data *prompt);

/* -----built-in----- */
void	ft_pwd(t_data *prompt);
void	ft_cd(t_data *promt);

/* -----minishell-----*/

/* ------heredoc----- */

#endif