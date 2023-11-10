/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:51:43 by jcoquard          #+#    #+#             */
/*   Updated: 2023/11/10 14:13:08 by edecoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/minishell.h"

#include <stdio.h>

int	g_rvalue;

int	say_hello(t_data *shell, char **envp)
{
	printf(YELLOW"===========================\n||"END);
	printf(RED" minishell !! patate ! "END);
	printf(YELLOW"||\n===========================\n"END);
	return (init_env(shell, envp));
}

void	say_bye(t_data *shell)
{
	clear_env(shell);
	ft_dprintf(2, "exit");
	printf(RED"\nbye bye patate!!\n"END);
}

int	main(int ac, char **av, char **envp)
{
	t_data	shell;

	(void)ac;
	(void)av;
	ft_bzero(&shell, sizeof(t_data));
	g_rvalue = 0;
	if (say_hello(&shell, envp))
		return (1);
	while (!shell.prompt.line | ft_strncmp(shell.prompt.line, "exit", 4))
	{
		prompt_signals();
		if (shell.prompt.line)
			free(shell.prompt.line);
		shell.prompt.line = readline(PRONPT);
		if (!shell.prompt.line)
			return (say_bye(&shell), free(shell.prompt.line), 0);
		if (shell.prompt.line[0] && !striswspace(shell.prompt.line))
			add_history(shell.prompt.line);
		pars(&shell);
		ft_env(&shell);
	}
	return (ft_exit(&shell, ft_split(shell.prompt.line, ' ')));
}
