/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:51:43 by jcoquard          #+#    #+#             */
/*   Updated: 2023/11/24 13:05:06 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/minishell.h"

int	g_rvalue;

int	say_hello(t_data *shell, char **envp)
{
	printf(YELLOW"===========================\n||"END);
	printf(RED" minishell !! patate ! "END);
	printf(YELLOW"||\n===========================\n"END);
	(void)envp;
	(void)shell;
	return (init_env(shell, envp));
}

void	say_bye(t_data *shell)
{
	rl_clear_history();
	if (shell->prompt.line)
		free(shell->prompt.line);
	if (shell->env)
		free_dtab(shell->env);
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
	while (ft_strcmp(shell.prompt.line, "exit"))
	{
		prompt_signals();
		if (shell.prompt.line)
			free(shell.prompt.line);
		shell.prompt.line = readline(RED"patate> "END);
		if (!shell.prompt.line)
			return (say_bye(&shell), 0);
		if (shell.prompt.line[0] && !striswspace(shell.prompt.line))
			add_history(shell.prompt.line);
		process(&shell);
		//break;
	}
	return (say_bye(&shell), 0);
}
