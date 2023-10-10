/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 17:17:07 by jcoquard          #+#    #+#             */
/*   Updated: 2023/09/11 14:30:41 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_pwd(t_data *prompt)
{
	char	*pwd;
	
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return;
	ft_dprintf(2, "%s\n", pwd);
	free(pwd);
}
