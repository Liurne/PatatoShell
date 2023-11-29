/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:58:51 by liurne            #+#    #+#             */
/*   Updated: 2023/11/28 17:04:23 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_env(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

int	is_var(char **env, char *var)
{
	int		i;
	int		len;

	i = -1;
	len = ft_strlen(var);
	if (!env)
		return (0);
	while (env && env[++i])
	{
		if (ft_strnstr(env[i], var, len) && (env[i][len] == '='
			|| !env[i][len]))
			return (1);
	}
	return (0);
}

char	*new_env_var(char *var, char *value, char *old_value)
{
	char	*tmp;
	char	*res;

	tmp = NULL;
	if (!value && !old_value)
		res = ft_strdup(var);
	else
	{
		if (value && *value != '=')
		{
			tmp = ft_strjoin(var, "=");
			if (!tmp)
				return (set_rval(1, ERR_MALLOC), NULL);
			if (!value)
				res = ft_strjoin(tmp, old_value);
			else
				res = ft_strjoin(tmp, value);
			free(tmp);
		}
		else
			res = ft_strjoin(var, value);
	}
	if (!res)
		return (set_rval(1, ERR_MALLOC), NULL);
	return (res);
}
