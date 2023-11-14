/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:59:29 by jcoquard          #+#    #+#             */
/*   Updated: 2023/11/14 19:16:16 by liurne           ###   ########.fr       */
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

void	capt_input(int *pipe, char *eof, int expand)
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
	(void)expand;
	//if (expand)
	//	expendfonction()
	ft_dprintf(pipe[1], heredoc);
	close(pipe[1]);
	close(pipe[0]);
	free(heredoc);
}

int	heredoc(t_cmd *cmd, char *eof, int expand)
{
	pid_t	pid;
	int		rval;

	if (pipe(cmd->pipe) == -1)
		return (set_rval(1, ERR_OPIPE));
	pid = fork();
	if (pid == -1)
		return (close(cmd->pipe[0]), close(cmd->pipe[1]), free(eof),
			set_rval(1, ERR_FORK));
	if (!pid)
	{
		capt_input(cmd->pipe, eof, expand);
		free (eof);
		if (g_rvalue)
			exit(g_rvalue);
		exit(g_rvalue);
	}
	close(cmd->pipe[1]);
	waitpid(pid, &rval, 0);
	return (set_rval(rval, NULL));
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
