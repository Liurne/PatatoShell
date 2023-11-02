/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:14:53 by liurne            #+#    #+#             */
/*   Updated: 2023/10/26 17:49:10 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	echo_option(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] =='-')
	{
		while (arg[i] && arg[i] == 'n')
			i++;
		if (!*arg && i > 1)
			return (1);
	}
	return (0);
}

char *echo_join(char **arg, int endl)
{
	char	*tmp;
	char	*res;
	int		i;

	i = 1 + endl;
	tmp = NULL;
	while (arg[i])
	{
		res = ft_strjoin(tmp, arg[i]);
		if (tmp)
			free(tmp);
		if (!res)
			return (ft_dprintf(2, ERR_MALLOC), NULL);
		if (arg[i + 1])
		{
			tmp = ft_strjoin(res, " ");
			free (res);
			if (!tmp)
				return (ft_dprintf(2, ERR_MALLOC), NULL);
		}
	}
	return (res);
}

int	ft_echo(char **arg)
{
	int		endl;
	char	*str;

	if (!arg[1])
		return(ft_dprintf(2, "\n"), 0);
	endl = 1 - echo_option(arg[1]);
	if (!endl && !arg[2])
		return (0);
	str = echo_join(arg, endl);
	if (endl)
		return (printf("%s\n", str), free(str), 0);
	return (printf("%s", str), free(str), 0);
}