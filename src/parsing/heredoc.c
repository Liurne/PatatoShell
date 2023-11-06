/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:59:29 by jcoquard          #+#    #+#             */
/*   Updated: 2023/11/06 18:17:02 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*update_string(int i, char *line, char *heredoc)
{
	char	*temp;

	if (i == 0)
	{
		heredoc = ft_strjoin(line, "\n");
		if (!heredoc)
			return (set_rval(1, ERR_MALLOC), NULL);
	}
	else
	{
		temp = ft_strjoin(heredoc, line);
		if (!temp)
			return (free(heredoc), set_rval(1, ERR_MALLOC), NULL);
		free(heredoc);
		heredoc = ft_strjoin(temp, "\n");
		if (!heredoc)
			return (free(temp), set_rval(1, ERR_MALLOC), NULL);
		free(temp);
	}
	return (heredoc);
}

void	capt_input(int *pipe, char *eof)
{
	char	*line;
	char	*heredoc;
	int		i;

	line = NULL;
	heredoc = NULL;
	i = 0;
	heredoc_signals();
	while (!g_rvalue)
	{
		if (line)
			free(line);
		line = readline(YELLOW"heredoc> "END);
		if (!line || !ft_strcmp(line, eof))
			break ;
		heredoc = update_string(i++, line, heredoc);
	}
	free(line);
	ft_dprintf(pipe[1], heredoc);
	if (dup2(pipe[0], STDIN_FILENO) == -1)
		set_rval(1, ERR_DUP2);
	close(pipe[1]);
	close(pipe[0]);
	free(heredoc);
}

int	heredoc(t_cmd *cmd, char *eof, int expand)
{
	pid_t	pid;

	if (pipe(cmd->pipe) == -1)
		return (set_rval(1, ERR_OPIPE));
	pid = fork();
	if (pid == -1)
		return (close(cmd->pipe[0]), close(cmd->pipe[1]), free(eof),
			set_rval(1, ERR_FORK));
	if (!pid)
	{
		capt_input(cmd->pipe, eof);
		free (eof);
		if (g_rvalue)
			exit(g_rvalue);
		if (expand)
		//	expendfonction()
		exit(g_rvalue);
	}
	if (pid)
		waitpid(pid, NULL, 0);
	return (0);
}

static int	get_heredocs(t_cmd *cmd, char *str, char c)
{
	int		i;
	char	*word;
	int		is_quote;

	(void)cmd;
	is_quote = 0;
	i = -1;
	while (str[++i] == c)
		str[i] = ' ';
	while (*(str + i) && ft_iswhitespace(get_pos(*(str + i))))
		str++;
	if (c == '<' && i == 2)
	{
		word = get_word(str + i, &is_quote);
		if (!word)
			return (2);
		heredoc(cmd, word, 1);
		free(word);
	}
	return (0);
}

int	pars_heredoc(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd[i])
	{
		if (cmd->cmd[i] == '<' || cmd->cmd[i] == '>')
			if (get_heredocs(cmd, cmd->cmd + i, *(cmd->cmd + i)))
				return (1);
		i++;
	}
	return (0);
}
