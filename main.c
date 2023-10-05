/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:51:43 by jcoquard          #+#    #+#             */
/*   Updated: 2023/10/04 17:47:24 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/minishell.h"

int	main(int ac, char** av, char **envp)
{
	t_data	prompt;

	(void)ac;
	(void)av;
	if (!envp || !envp[0] || !ft_strncmp("PATH", *envp, 4))
		return (printf("Error: environment non existent\n"), 1);
	ft_bzero(&prompt, sizeof(t_data));
	printf(YELLOW"===========================\n||"END);
	printf(RED" minishell !! patate ! "END);
	printf(YELLOW"||\n===========================\n"END);
	while (ft_strcmp(prompt.line.line, "exit"))
	{
		if (prompt.line.line)
			free(prompt.line.line);
		prompt.line.line = readline(RED"patate> "END);
		if (!prompt.line.line)
		{
			printf("exit");
			printf(RED"\nbye bye patate!!\n"END);
			free(prompt.line.line);
			return (0);
		}
		if (prompt.line.line[0])
			add_history(prompt.line.line);
		pars(&prompt);
		free_cmd(&prompt);
		if (!ft_strcmp(prompt.line.line, "pwd"))
		{
			char	*pwd = getcwd(NULL, 0);
			ft_dprintf(2, "%s\n", pwd);
			free(pwd);
		}
		if (!ft_strcmp(prompt.line.line, "slt"))
			ft_dprintf(2, "%s %d\n", ", ca va ?", 8);
	}
	printf(RED"bye bye patate!!\n"END);
	free(prompt.line.line);
	return (0);
}