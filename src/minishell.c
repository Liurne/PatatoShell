/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:20:04 by jcoquard          #+#    #+#             */
/*   Updated: 2023/06/03 13:54:56 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//penser au char spe : " ' * $ | <<
//si "" bien copier tout le  contenu
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
//cd ne marche pas dans des pipes (car le cd ce fait dans le child mais executer quand meme)
//message d'erreur pour cd si HOME unset