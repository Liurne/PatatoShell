/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:20:04 by jcoquard          #+#    #+#             */
/*   Updated: 2023/11/21 17:46:09 by jcoquard         ###   ########.fr       */
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

void	exec_sigint(int sig)
{
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	g_rvalue = 128 + sig;
}

void	exec_sigquit(int sig)
{
	ft_putendl_fd("Quit (core dumped)", 2);
	g_rvalue = 128 + sig;
}

void	heredoc_sigint(int sig)
{
	g_rvalue = 128 + sig;
	printf("\n");
	//ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}
