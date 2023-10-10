/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:51:43 by jcoquard          #+#    #+#             */
/*   Updated: 2023/10/06 16:54:10 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/minishell.h"

void say_hello()
{
	printf(YELLOW"===========================\n||"END);
	printf(RED" minishell !! patate ! "END);
	printf(YELLOW"||\n===========================\n"END);
}

void say_bye()
{
	printf(RED"\nbye bye patate!!\n"END);
}

int	main(int ac, char** av, char **envp)
{
	t_data	shell;

	(void)ac;
	(void)av;
	(void)envp;
	ft_bzero(&shell, sizeof(t_data));
	say_hello();
	while (ft_strcmp(shell.prompt.line, "exit"))
	{
		if (shell.prompt.line)
			free(shell.prompt.line);
		shell.prompt.line = readline(RED"patate> "END);
		if (!shell.prompt.line)
		{
			printf("exit");
			return (say_bye(), free(shell.prompt.line), 0);
		}
		if (shell.prompt.line[0] && !ft_striswspace(shell.prompt.line))
			add_history(shell.prompt.line);
		pars(&shell);
	}
	return (say_bye(), free(shell.prompt.line), 0);
}
