/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sortedstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:11:01 by liurne            #+#    #+#             */
/*   Updated: 2023/12/01 13:06:36 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include <stdio.h>
#include <string.h>

static char	*get_name(char *str)
{
	char	*word;

	word = NULL;
	while (*str && *str != '=')
	{
		word = ft_addchar(word, *str);
		if (!word)
			return (NULL);
		str++;
	}
	if (!word)
		return (NULL);
	return (word);
}

int	find_index(char **strs, int start, int end, int min)
{
	if (start > end)
		return (min);
	if (ft_strcmp(strs[start], strs[min]) < 0)
		return (find_index(strs, start + 1, end, start));
	else
		return (find_index(strs, start + 1, end, min));
}

void	put_sortedstr(char **strs, int start, int end)
{
	int		min;
	char	*tmp;
	char	*var;

	if (start > end)
		return ;
	min = find_index(strs, start, end, start);
	tmp = strs[start];
	strs[start] = strs[min];
	strs[min] = tmp;
	var = get_name(strs[start]);
	if (var)
	{
		if (strs[start][ft_strlen(var)])
			printf("%s=\"%s\"\n", var, strs[start] + ft_strlen(var) + 1);
		else
			printf("%s\n", var);
		free(var);
	}
	put_sortedstr(strs, start + 1, end);
}
