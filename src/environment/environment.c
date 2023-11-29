/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:03:11 by liurne            #+#    #+#             */
/*   Updated: 2023/11/28 18:29:08 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_env(t_data *shell)
{
	int	i;

	i = 0;
	if (!shell->env)
		return ;
	while (shell->env[i])
	{
		free(shell->env[i]);
		i++;
	}
	free(shell->env);
}

int	del_var(t_data *shell, char *var)
{
	int		i;
	int		j;
	int		len;
	char	**tmp;

	tmp = (char **)ft_calloc(len_env(shell->env), sizeof(char *));
	if (!tmp)
		return (set_rval(1, ERR_MALLOC));
	i = -1;
	j = 0;
	len = ft_strlen(var);
	while (shell->env && shell->env[++i])
	{
		if (!ft_strnstr(shell->env[i], var, len) && 
			(shell->env[i][len] || shell->env[i][len] != '='))
		{
			tmp[j] = ft_strdup(shell->env[i]);
			if (!tmp[j])
				return (free_dtab(tmp), set_rval(1, ERR_MALLOC));
			j++;
		}
	}
	return (clear_env(shell), shell->env = tmp, set_rval(0, NULL));
}

int	add_var(t_data *shell, char *var, char *value)
{
	char	**tmp;
	int		i;
	int		j;

	if (is_var(shell->env, var))
		tmp = (char **)ft_calloc(len_env(shell->env) + 1, sizeof(char *));
	else
		tmp = (char **)ft_calloc(len_env(shell->env) + 2, sizeof(char *));
	if (!tmp)
		return (set_rval(1, ERR_MALLOC));
	tmp[0] = new_env_var(var, value, get_env_var(shell, var));
	if (!tmp[0])
		return (free_dtab(tmp), set_rval(1, ERR_MALLOC));
	i = -1;
	j = 0;
	while (shell->env && shell->env[++i])
	{
		if (!ft_strnstr(shell->env[i], var, ft_strlen(var)) &&
			(shell->env[i][ft_strlen(var)] || shell->env[i][ft_strlen(var)] != '='))
			tmp[++j] = ft_strdup(shell->env[i]);
		if (!tmp[j])
			return (free_dtab(tmp), set_rval(1, ERR_MALLOC));
	}
	return (clear_env(shell), shell->env = tmp, set_rval(0, NULL));
}

int	init_env(t_data *shell, char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
		i++;
	if (!i)
		return (shell->env = NULL, 0);
	shell->env = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!shell->env)
		return (set_rval(1, ERR_MALLOC));
	i = 0;
	while (envp[i])
	{
		shell->env[i] = ft_strdup(envp[i]);
		if (!shell->env[i])
			return (clear_env(shell), set_rval(1, ERR_MALLOC));
		i++;
	}
	return (0);
}

char	*get_env_var(t_data *shell, char *var)
{
	int		i;
	int		len;

	i = -1;
	len = ft_strlen(var);
	if (!shell->env)
		return (NULL);
	while (shell->env[++i])
	{
		if (ft_strnstr(shell->env[i], var, len) && shell->env[i][len] == '=')
			return (shell->env[i] + len + 1);
	}
	return (NULL);
}
