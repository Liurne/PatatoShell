/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 19:13:52 by jcoquard          #+#    #+#             */
/*   Updated: 2023/11/15 17:01:57 by jcoquard         ###   ########.fr       */
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
		return (-1);
	if (*var == '$')
		return (free(var), 1);
	res = ft_strlen(var) + 1;
	if (*var == '?')
	{
		tmp = ft_itoa(g_rvalue);
		if (!tmp)
			return (set_rval(1, ERR_MALLOC));
	}
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

static int	true_len(t_data *shell, char *cmd)
{
	int		len;
	int		tmp;
	t_quote	quote;

	len = 0;
	ft_bzero(&quote, sizeof(t_quote));
	while (*cmd)
	{
		manage_quote(*cmd, &quote);
		if (*cmd == '$' && !quote.s)
		{
			tmp = get_len_var(shell, cmd, &len);
			if (tmp == -1)
				return (-1);
			cmd += tmp;
		}
		else
			cmd++;
		len++;
	}
	return (len);
}

char	*expand(t_data *shell, char *line)
{
	char	*res;
	t_quote	quote;
	int		i;
	int		j;

	ft_bzero(&quote, sizeof(t_quote));
	i = 0;
	j = 0;
	res = ft_calloc(true_len(shell, line) + 1, sizeof(char));
	if (!res)
		return (set_rval(1, ERR_MALLOC), NULL);
	while (line[i])
	{
		manage_quote(line[i], &quote);
		if (line[i] == '$' && !quote.s)
			i+= put_var(shell, line + i, res, &j);
		else
			res[j] = line[i];
		j++;
		i++;
	}
	free(line);
	return (res);
}
