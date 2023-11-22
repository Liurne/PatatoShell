/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:09:12 by edecoste          #+#    #+#             */
/*   Updated: 2023/11/22 14:04:38 by edecoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// DEBUT pas encore teste
int	add_to_env_end(t_data *shell, char *new_element)
{
	char	**new_env;
	int		argc;
	int		i;

	argc = 0;
	i = 0;
	while (shell->env[argc])
		argc++;
	new_env = malloc(sizeof(char *) * (1 + ++argc));
	if (!new_env)
		return (EXIT_FAILURE);
	while (i < argc - 1)
	{
		new_env[i] = ft_strdup(shell->env[i]);
		if (!new_env[i])
			return (EXIT_FAILURE);
		i++;
	}
	new_env[i] = ft_strdup(new_element);
	if (!new_env[1])
		return (EXIT_FAILURE);
	new_env[++i] = NULL;

	free_dtab(shell->env);
	shell->env = new_env;
	return (EXIT_SUCCESS);
}

int	add_to_env_existing(t_data *shell, char *new_element)
{
	(void)shell;
	(void)new_element;
	return (EXIT_SUCCESS);
}

// new arg name can only be a alphanumeric char or _ 
// new arg name can't start by number
// new arg value should be interpreted if valide like : "salut$USER" = "salutedecoste", "salut$nimportkwa" = "salut"
// new arg value can contain multiple interpretde value

int valide_arg(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]))
		return (EXIT_FAILURE);
	while (str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (EXIT_FAILURE);
		i++;
	}
	if (str[i] && str[i] == '=')
		return (2);
	return (EXIT_SUCCESS);
}

int	alreadyin(t_data *shell, char *new_element)
{
	int	i;

	i = 0;
	while (ft_strchr(shell->env[i], new_element))
	{
		printf("oui");
		return (EXIT_SUCCESS);
	}
	
	return (EXIT_FAILURE);
}

void	ft_export(t_data *shell, char **argv, int pid)
{
	int	argc;
	int	i;

	argc = 0;
	(void)pid;
	while (argv[argc])
		argc++;
	i = -1;
	while (argc == 1 && shell->env[++i])
		if (ft_strchr(shell->env[i], '='))
			printf("%s\n", shell->env[i]);
	if (argc >= 2)
	{
		// if = found with space around error: bad assignment
		while (++i < argc)
		{
			if (!alreadyin(shell, argv[i]) && valide_arg(argv[i]) == 2)
				add_to_env_existing(shell, argv[i]);
			else if (valide_arg(argv[i]) == 0)
				add_to_env_end(shell, argv[i]);
			else
				printf("export: not valid in this context: %s\n", argv[i]);
		}
	}
}