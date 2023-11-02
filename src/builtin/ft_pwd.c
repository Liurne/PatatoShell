/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:27:40 by liurne            #+#    #+#             */
/*   Updated: 2023/10/26 17:47:36 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd()
{
	char	*buff;
	
	buff = getcwd(NULL, 0);
	if (!buff)
		return (ft_dprintf(2, "patate: sorry but you're lost\n"), 1);
	printf("%s\n", buff);
	free(buff);
	return (0);
}