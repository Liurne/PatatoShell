/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:03:33 by edecoste          #+#    #+#             */
/*   Updated: 2023/11/02 16:46:17 by edecoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
		str[i++] = 0;
}

char	*update_string(int i, char *line, char *heredoc)
{
	char	*temp;

	if (i == 0)
	{
		heredoc = ft_strjoin(line, "\n");
		if (!heredoc)
			return (free(line), \
					ft_dprintf(2, "patate: heredoc ft_strjoin\n"), NULL);
		free(line);
	}
	else
	{
		temp = ft_strjoin(heredoc, line);
		if (!temp)
			return (free(heredoc), free(line), \
					ft_dprintf(2, "patate: heredoc ft_strjoin\n"), NULL);
		free(heredoc);
		heredoc = ft_strjoin(temp, "\n");
		if (!heredoc)
			return (free(line), free(temp), \
					ft_dprintf(2, "patate: heredoc ft_strjoin\n"), NULL);
		free(line);
		free(temp);
	}
	return (heredoc);
}

void	capt_input(int *here_fd, char *eof)
{
	char	*line;
	char	*heredoc;
	int		i;

	i = 0;
	heredoc = NULL;
	heredoc_signals();
	while (g_rvalue != 130)
	{
		line = readline("heredoc> ");
		if ((ft_strlen(line) > 0 && !ft_strcmp(line, eof)) || !line)
			break ;
		heredoc = update_string(i++, line, heredoc);
	}
	ft_dprintf(here_fd[1], heredoc);
	if (dup2(here_fd[0], STDIN_FILENO) == -1)
		ft_dprintf(2, "patate: heredoc stdin\n");
	close(here_fd[1]);
	close(here_fd[0]);
	free(heredoc);
}

void	heredoc(int do_expend, char *eof)
{
	int		here_fd[2];
	char	*input;
	pid_t	pid;

	input = NULL;
	if (pipe(here_fd) == -1)
	{
		ft_dprintf(2, "patate: heredoc pipe\n");
		return (free(eof));
	}
	pid = fork();
	if (pid == -1)
		ft_dprintf(2, "patate: heredoc fork\n");
	if (pid == 0)
	{
		capt_input(here_fd, eof);
		if (g_rvalue == 130)
			return (free(eof), exit(1));
		if (do_expend)
		//	expendfonction()
		return (free(eof), exit(1));
	}
	if (pid)
		waitpid(pid, NULL, 0);
	return ;
}
