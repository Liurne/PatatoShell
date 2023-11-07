/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:41:12 by edecoste          #+#    #+#             */
/*   Updated: 2023/11/07 15:16:39 by edecoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// exit -1 return 255
// exit -2 return 254
// exit 254 return 254
// exit 255 return 255
// exit 256 return 0
// exit 257 return 1
// exit 258 return 2
// La valeur de retour est modulo par 255 

// exit {{number}} {{number}} dont exit with an error : "exit: too many arguments"
// exit {{text}} {{numbe}} return 2 with an error : "exit: {{text}}: numeric argument required"
// exit {{number}} {{text}} dont exit with an error : "exit: too many arguments"
// exit {{text1}} {{text2}} return 2 with an error : "exit: {{text1}}: numeric argument required"

// Si le premiere element est un nombre on exit pas
int	free_tab(int len, char **tab)
{
	int	i;

	i = 0;
	while (i < len)
		free(tab[i++]);
	return (free(tab), 1);
}

// static char	*ft_skipws(char *str)
// {
// 	while (((str[0] > 8) & (str[0] < 14)) || str[0] == ' ')
// 		str++;
// 	return (str);
// }

// bug in atoi -9223372036854775809 should overflow but it return 9223372036854775807
int	valide_number(char *str)
{
	long long	temp;
	// char		*str_cpy;

	temp = ft_atoi_ll(str);
	// str_cpy = ft_strdup(str);
	// strlen should skip space and tabs...
	// printf("1%s\n", str_cpy);
	// printf("2%s\n", ft_skipws(str_cpy));
	// printf("3%s\n", str_cpy);
	if ((temp == 0 || temp == -1) && ft_strlen(str) > 1)
		return (EXIT_FAILURE);
	if (!ft_strcmp(str, "0") || temp != 0)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	is_valide_argv(char *arg, int argc)
{
	if (argc == 1)
	{
		g_rvalue = 0;
		ft_dprintf(1, "exit\n");
		return (1);
	}
	else if (!valide_number(arg) && argc > 2)
	{
		ft_dprintf(1, "exit\n%sexit: too many arguments", PRONPT);
		return (0);
	}
	else if (!valide_number(arg) && argc == 2)
	{
		g_rvalue = ft_atoi(arg) % 256;
		ft_dprintf(1, "exit\n");
		return (1);
	}
	g_rvalue = 2;
	printf("exit\n%sexit: %s: numeric argument required\n", PRONPT, arg);
	return (2);
}

// creat a line copy that skip the first word and space after it the line must stop at att the first space after the second part
// "exit salut coucou" must return "salut"
int	ft_exit(t_data *shell, char *line)
{
	char **splited_line;
	int	argc;
	int return_type;

	splited_line = ft_split2(line, ' ');
	printf("split[1]: %s\n", splited_line[1]);
	argc = count_words(line, ' ');
	return_type = is_valide_argv(splited_line[1], argc);
	if (return_type == 1 || return_type == 2)
		clear_env(shell);
	free_tab(count_words(line, ' '), splited_line);
	free(line);
	return (g_rvalue);
}