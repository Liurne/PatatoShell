/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:51:40 by jcoquard          #+#    #+#             */
/*   Updated: 2023/06/28 14:08:54 by jcoquard         ###   ########.fr       */
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

//penser au char spe : " ' * $ | <<
//si "" bien copier tout le contenu
//si '%2 = 1 || "%2 = 1 planter (ne pas conter le contenue entre guillemet)
//<< si 0 mot apres planter (le mot peut etre une commande)
//retirer tout les espaces n'etant pas entre guillemet
//$ a gerer meme entre quote ($$ pas a gerer)
// fonction aui detecte les $ et les exands directe peut importe la situation
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

typedef struct s_cmd
{
	char	**cmd;
	bool	heredocs;
	char	*d_heredocs;
	int		infile;
	int		outfile;
	int		fd[2];
	bool	redir;
}	t_cmd;

typedef struct s_data
{
	char	*line;
	t_cmd	*cmds;
}	t_data;

/* -----utils----- */

/* -----minishell-----*/

/* ------heredoc----- */

#endif