/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 17:16:55 by jcoquard          #+#    #+#             */
/*   Updated: 2023/09/12 23:40:30 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd(t_data *prompt, t_cmd *cmd)
{
	char	*home_path;

	home_path = get_env_var("HOME");
	if (!args[0])
	{
		change_dir(home_path, 0);
		return;
	}
	if (has_two_args(args))
		return;
	else
		change_dir(args[0], 0);
}


int				cd_builtin(char **args)
{
	char	*home_path;

	home_path = get_env_var("HOME");
	if (!args[0])
	{
		change_dir(home_path, 0);
		return (1);
	}
	if (has_two_args(args))
		return (1);
	else
	{
		if (ft_strequ(args[0], "--"))
		{
			change_dir(home_path, 0);
			return (1);
		}
		else if (args[0][0] == '-' && !args[0][2])
		{
			change_dir(get_env_var("OLDPWD"), 1);
			return (1);
		}
		change_dir(args[0], 0);
	}
	return (1);
}