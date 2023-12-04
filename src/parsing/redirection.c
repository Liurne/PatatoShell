/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:35:15 by jcoquard          #+#    #+#             */
/*   Updated: 2023/12/04 13:18:03 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_fd(char *str)
{
	int		i;
	t_quote	quote;
	char	*word;

	i = -1;
	ft_bzero(&quote, sizeof(t_quote));
	word = NULL;
	while (str[++i] && ((!ft_iswhitespace(get_pos(str[i]))
				&& str[i] != '<' && str[i] != '>'
				&& str[i] != '|') || quote.d || quote.s))
	{
		if (str[i] == '"' || str[i] == '\'')
			manage_quote(str[i], &quote);
		else
		{
			word = ft_addchar(word, get_pos(str[i]));
			if (!word)
				return (NULL);
		}
		str[i] = ' ';
	}
	return (word);
}

static int	set_redirin(t_cmd *cmd, char *word, t_redir redir)
{
	if (redir == INFILE)
	{
		if (cmd->infile)
			ft_close (&(cmd->infile));
		cmd->infile = open(word, O_RDONLY);
		if (cmd->infile == -1)
			return (ft_dprintf(2, "patate: no such file or directory: %s\n"
					, word, set_rval(1, NULL)));
		cmd->redir_in = INFILE;
	}
	if (redir == HEREDOC)
	{
		if (cmd->infile)
			ft_close (&(cmd->infile));
		cmd->infile = cmd->pipe[0];
		cmd->pipe[0] = 0;
		cmd->redir_in = HEREDOC;
	}
	return (0);
}

static int	set_redirout(t_cmd *cmd, char *word, t_redir redir)
{
	if (redir == OUTFILE)
	{
		if (cmd->outfile)
			ft_close (&(cmd->outfile));
		cmd->outfile = open(word, O_TRUNC | O_CREAT | O_RDWR, 0000644);
		if (cmd->outfile == -1)
			return (ft_dprintf(2, "patate: couldn't create file: %s\n"
					, word, set_rval(1, NULL)));
	}
	if (redir == OUTAPPEND)
	{
		if (cmd->outfile)
			ft_close (&(cmd->outfile));
		cmd->outfile = open(word, O_APPEND | O_CREAT | O_RDWR, 0000644);
		if (cmd->outfile == -1)
			return (ft_dprintf(2, "patate: couldn't create file: %s\n"
					, word, set_rval(1, NULL)));
	}
	return (0);
}

static int	get_redir(t_cmd *cmd, char *str, char c)
{
	int		i;
	char	*word;
	int		open_fail;

	open_fail = 0;
	i = -1;
	while (str[++i] == c)
		str[i] = ' ';
	while (*(str + i) && ft_iswhitespace(get_pos(*(str + i))))
		str++;
	word = get_fd(str + i);
	if (c == '<' && i == 1)
		open_fail = set_redirin(cmd, word, INFILE);
	if (c == '<' && i == 2)
		open_fail = set_redirin(cmd, word, HEREDOC);
	if (c == '>' && i == 1)
		open_fail = set_redirout(cmd, word, OUTFILE);
	if (c == '>' && i == 2)
		open_fail = set_redirout(cmd, word, OUTAPPEND);
	if (open_fail)
		return (free(word), 1);
	return (free(word), 0);
}

int	pars_redir(t_cmd *cmd)
{
	int	i;
	t_quote quote;

	ft_bzero(&quote, sizeof(t_quote));
	i = 0;
	while (cmd->cmd && cmd->cmd[i])
	{
		manage_quote(cmd->cmd[i], &quote);
		if (!quote.s && !quote.d && (cmd->cmd[i] == '<' || cmd->cmd[i] == '>'))
		{
			if (get_redir(cmd, cmd->cmd + i, *(cmd->cmd + i)))
				return (1);
		}
		i++;
	}
	return (0);
}
