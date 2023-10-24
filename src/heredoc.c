/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:03:33 by edecoste          #+#    #+#             */
/*   Updated: 2023/10/18 17:13:52 by edecoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	l;
	size_t	i;
	size_t	j;
	char	*res;

	i = 0;
	j = 0;
	l = ft_strlen(s1) + ft_strlen(s2) + 1;
	res = (char *)malloc(l * sizeof(char));
	if (res == NULL)
		return (NULL);
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	if (s1)
		free(s1);
	while (s2 && s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[l - 1] = '\0';
	return (res);
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

void	capt_input(int here_pipe, char *eof, int do_expend)
{
	char *rt;
	char *join;

	// rt = readline("prompt: ");
	join = malloc(sizeof(char));
	// join = rt;
	// putendl_fd(rt, 2);
	while (1)
	{
		rt = readline("prompt: ");
		if (!ft_strncmp(rt, eof, ft_strlen(rt)))
			break ;
		join = ft_strjoin(join, rt);
		join = ft_strjoin(join, "\n");
	}
	// dup2(pipe[0], 0);
	if (dup2(pipe[1], 1) == -1)
		ft_putstr_fd("Error: dup2 didn't work\n", 2);
	(void)do_expend; // if do_expend run the expend fonction on join
	// putendl_fd("no", 0);
	*str = join;
}

void heredoc(char *eof)
{
	int here_pipe[2];
	char *str;

	pipe(here_pipe); // cree un lien en here_pipe[0] et here_pipe[1]

	pid_t pid = fork(); // cree un nouveau processuse
	if (pid == -1) // le fork n'as pas marche
		putendl_fd("Error: fork\n", 2);
	if (pid == 0) // si 0 je me trouve actuellement dans mon enfants
		capt_input(here_pipe, eof);
	if (pid)
		waitpid(pid, NULL, 0);
	putendl_fd(str, 2);
	return ;
}

int main(int argc, char **argv)
{
	// t_data data;

	// ft_bzero(&data, sizeof(t_data));
	if (argc != 2)
		return (0);
	heredoc(argv[1]);
	return (0);
}