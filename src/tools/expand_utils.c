/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:37:59 by liurne            #+#    #+#             */
/*   Updated: 2023/10/25 15:24:46 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_varname(char *str)
{
	char	*word;

	word = NULL;
	if (!*str || *str == '$' || ft_iswhitespace(*str))
	{
		word = ft_addchar(word, '$');
		return (word);
	}
	if (*str == '?')
	{
		word = ft_addchar(word, '?');
		return (word);
	}
	while (*str && (!ft_iswhitespace(*str) && *str != '\''
			&& *str != '"' && *str != '$'))
	{
		word = ft_addchar(word, *str);
		if (!word)
			return (NULL);
		str++;
	}
	return (word);
}

int	get_len_var(t_data *shell, char *str, int *len)
{
	char	*var;
	char	*tmp;
	int		res;

	var = get_varname(str + 1);
	if (!var)
		return (1);
	if (*var == '$')
		return (free(var), 1);
	res = ft_strlen(var) + 1;
	if (*var == '?')
		tmp = ft_itoa(g_rvalue);
	else
		tmp = get_env_var(shell, var);
	if (!tmp)
		return (free(var), res);
	*len = *len + ft_strlen(tmp);
	if (*var == '?')
		free(tmp);
	free(var);
	return (res);
}

int	put_var(t_data *shell, char *str, char *dst, int *i)
{
	char	*var;
	char	*tmp;
	int		res;

	var = get_varname(str + 1);
	dst += *i;
	if (!var)
		return (0);
	if (*var == '$')
		return (*dst = '$', free(var), 0);
	res = ft_strlen(var);
	if (*var == '?')
		tmp = ft_itoa(g_rvalue);
	else
		tmp = get_env_var(shell, var);
	if (!tmp)
		return ((*i)--, free(var), res);
	*i += ft_strlen(tmp) - 1;
	strcpy_neg(dst, tmp, ft_strlen(tmp) + 1);
	if (*var == '?')
		free(tmp);
	return (free(var), res);
}
