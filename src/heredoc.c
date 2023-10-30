/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:03:33 by edecoste          #+#    #+#             */
/*   Updated: 2023/10/30 16:32:49 by edecoste         ###   ########.fr       */
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

char	*capt_input(int *here_pipe, char *eof)
{
	char	*line;
	char	*heredoc;
	int		i;

	(void)here_pipe;
	i = 0;
	heredoc = NULL;
	heredoc_signals();
	while (g_rvalue != 130)
	{
		line = readline("heredoc> ");
		if (ft_strlen(line) > 0 && !ft_strcmp(line, eof))
			break ;
		heredoc = update_string(i, line, heredoc);
		
		i++;
	}
	return (heredoc);
}

void heredoc(int do_expend, char *eof)
{
	int		here_pipe[2];
	char	*input;

	input = NULL;
	pipe(here_pipe); // cree un lien en here_pipe[0] et here_pipe[1]

	pid_t pid = fork(); // cree un nouveau processuse
	if (pid == -1) // le fork n'as pas marche
		putendl_fd("Error: fork\n", 2);
	if (pid == 0) // si 0 je me trouve actuellement dans mon enfants
	{
		input = capt_input(here_pipe, eof);
		if (g_rvalue == 130)
		{
			putendl_fd(input, 0); // debug
			if (input)
				free(input);
			free(eof);
			// close heredoc
			exit(1);
		}
		if (do_expend)
		{
			// expendfonction(input)
		}
		if (input)
		{
			putendl_fd("--", 0); // debug
			putendl_fd(input, 0); // debug
			putendl_fd("--", 0); // debug
		}
		free(eof);
		free(input);
		exit(1);
	}
	if (pid)
	{
		waitpid(pid, NULL, 0);
		free(eof);
	}
	return ;
}

// int main(int argc, char **argv)
// {
// 	// t_data data;

// 	// ft_bzero(&data, sizeof(t_data));
// 	if (argc != 2)
// 		return (0);
// 	heredoc(argv[1]);
// 	return (0);
// }