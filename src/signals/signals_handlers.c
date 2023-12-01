/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:20:04 by jcoquard          #+#    #+#             */
/*   Updated: 2023/12/01 13:05:21 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	prompt_sigint(int sig)
{
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_rvalue = 128 + sig;
}

void	exec_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		g_rvalue = 128 + sig;
	}
	if (sig == SIGQUIT)
	{
		ft_putendl_fd("Quit (core dumped)", 2);
		g_rvalue = 128 + sig;
	}
}

void	heredoc_sigint(int sig)
{
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	g_rvalue = 128 + sig;
}
