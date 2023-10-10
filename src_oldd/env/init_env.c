/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:32:26 by jcoquard          #+#    #+#             */
/*   Updated: 2023/07/20 15:41:28 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	clear_env(char **env, int nb_v)
{
	int	i;

	i = 0;
	while((nb_v == -1 && env[i]) || (nb_v != -1 && i < nb_v))
	{
		free(env[i]);
		i++;
	}
	free(env);
}
char	**create_env(char **envp)
{
	int		i;
	char	**new_env;

	i = 0;
	while(envp[i])
		i++;
	new_env = (char **)ft_calloc(i, sizeof(char *))
	if (!new_env)
		return (NULL);
	i = 0;
	while(envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		if(!new_env[i])
			return(clear_env(new_env, i), NULL);
		i++;
	}
	return (new_env);
}