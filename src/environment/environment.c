/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:03:11 by liurne            #+#    #+#             */
/*   Updated: 2023/10/27 19:26:39 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_env(t_data *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		free(shell->env[i]);
		i++;
	}
	free(shell->env);
}

int	init_env(t_data *shell, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	if (!i)
		return (shell->env = NULL, 0);
	shell->env = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!shell->env)
		return (set_rval(2, ERR_MALLOC));
	i = 0;
	while (envp[i])
	{
		shell->env[i] = ft_strdup(envp[i]);
		if (!shell->env[i])
			return (clear_env(shell), set_rval(2, ERR_MALLOC));
		i++;
	}
	shell->env[i] = NULL;
	return (0);
}

char	*get_env_var(t_data *shell, char *var)
{
	int		i;
	int		len;

	i = -1;
	len = ft_strlen(var);
	while (shell->env[++i])
	{
		if (ft_strnstr(shell->env[i], var, len) && shell->env[i][len] == '=')
			return (shell->env[i] + len + 1);
	}
	return (NULL);
}
