/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:59:29 by jcoquard          #+#    #+#             */
/*   Updated: 2023/11/29 18:05:39 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*update_string(int i, char *line, char *heredoc)
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

static void	capt_input(t_data *shell, int *pipe, char *eof, int is_expand)
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
	if (is_expand && heredoc)
		heredoc = expand(shell, heredoc);
	ft_dprintf(pipe[1], strpos(heredoc));
	return (close(pipe[1]), close(pipe[0]), free(heredoc));
}

static int	heredoc(t_data *shell, t_cmd *cmd, char *eof, int expand)
{
	pid_t	pid;
	int		rval;

	if (cmd->pipe[0])
		ft_close(&(cmd->pipe[0]));
	if (cmd->pipe[1])
		ft_close(&(cmd->pipe[1]));
	if (pipe(cmd->pipe) == -1)
		return (set_rval(1, ERR_OPIPE));
	set_rval(0, NULL);
	pid = fork();
	if (pid == -1)
		return (ft_close(&(cmd->pipe[0])), ft_close(&(cmd->pipe[1])),
			free(eof), set_rval(1, ERR_FORK));
	if (!pid)
	{
		capt_input(shell, cmd->pipe, eof, expand);
		free (eof);
		free_cmds(shell);
		exit(g_rvalue);
	}
	waitpid(pid, &rval, 0);
	ft_close(&(cmd->pipe[1]));
	return (set_rval(rval, NULL));
}

static int	get_heredocs(t_data *shell, t_cmd *cmd, char *str, char c)
{
	int		i;
	char	*word;
	int		is_quote;

	(void)cmd;
	is_quote = 0;
	i = 0;
	while (str[i] == c)
		i++;
	while (*(str + i) && ft_iswhitespace(get_pos(*(str + i))))
		str++;
	if (c == '<' && i == 2)
	{
		word = geteof(str + i, &is_quote);
		if (!word)
			return (2);
		unplug_signals();
		heredoc(shell, cmd, word, 1);
		prompt_signals();
		free(word);
	}
	return (0);
}

int	pars_heredoc(t_data *shell, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd[i])
	{
		if (cmd->cmd[i] == '<' && cmd->cmd[i + 1] == '<')
			if (get_heredocs(shell, cmd, cmd->cmd + i, *(cmd->cmd + i)))
				return (1);
		i++;
	}
	return (0);
}
