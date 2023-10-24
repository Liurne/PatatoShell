/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:27:01 by edecoste          #+#    #+#             */
/*   Updated: 2023/10/10 15:46:01 by edecoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>

void sigint_handler(int signal)
{
	if (signal == SIGINT)
		printf("\nctrl c presed\n");
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

void	set_signal_action(void)
{
	struct sigaction	sa;
	
	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = &sigint_handler;
	sigaction(SIGINT, &sa, NULL);
}

int main(void)
{
	set_signal_action();
	while(1)
		continue ;
}