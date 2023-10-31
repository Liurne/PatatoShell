/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:03:33 by edecoste          #+#    #+#             */
/*   Updated: 2023/10/31 17:01:38 by edecoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// comprendre heredoc : https://linuxize.com/post/bash-heredoc/

void	putendl_fd(char *s, int fd)
{
	size_t	i;
	int		rt_val;

	i = 0;
	rt_val = 0;
	if (!s)
		putendl_fd("(null)", fd);
	else
	{
		while (s[i])
			i++;
		rt_val = write(fd, s, i);
		if (rt_val == -1)
			return ;
	}
	write(fd, "\n", 2);
	return ;
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
		str[i++] = 0;
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((unsigned char)s1[i] && (unsigned char)s1[i] == \
	(unsigned char)s2[i] && n > 0)
	{
		n--;
		i++;
	}
	if (n == 0)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*update_string(int i, char *line, char *heredoc)
{
	char	*temp;

	if (i == 0)
	{
		heredoc = ft_strjoin(line, "\n");
		free(line);
	}
	else
	{
		temp = ft_strjoin(heredoc, line); // protecte join
		free(heredoc);
		heredoc = ft_strjoin(temp, "\n"); // protecte join
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
	dup2(here_fd[0], STDIN_FILENO);
	close(here_fd[1]);
	close(here_fd[0]);
	free(heredoc);
}

void heredoc(int do_expend, char *eof)
{
	int		here_fd[2];
	char	*input;

	input = NULL;
	if (pipe(here_fd) == -1)
		return (putendl_fd("Error: heredoc pipe\n", 2));
	pid_t pid = fork();
	if (pid == -1)
		putendl_fd("Error: fork\n", 2);
	if (pid == 0)
	{
		capt_input(here_fd, eof);
		if (g_rvalue == 130)
			return (free(eof), exit(1));
		if (do_expend)
		{
			// expendfonction()
		}
		return (free(eof), exit(1));
	}
	if (pid)
		waitpid(pid, NULL, 0);
	return ;
}
