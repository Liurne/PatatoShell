/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:14:59 by liurne            #+#    #+#             */
/*   Updated: 2023/10/03 14:21:34 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.c"

int redirection_pars();
int heredocs_pars();

int	brackets_pars(t_data *line, t_cmd *cmd, unsigned int i)
{
	int		chevron;

	chevron = 0;
	while (cmd->cmd[i] == '<')
		chevron++;
	if (chevron > 3)
	{
		ft_dprintf(2, "patate: %s \'",ERR_SYNTAX);
		while(chevron-- - 2)
			ft_putchar_fd('<', 2);
		return (1, ft_dprintf(2, "\'\n"));
	}
	if (chevron == 3)
		return(1, ft_dprintf(2, "patate: our shell doesn\'t manage '<<<'\n"));
	if (chevron == 2)
	{
		
	}
	if (chevron == 1)
	return (0);
}