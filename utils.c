/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 22:52:27 by oelharbi          #+#    #+#             */
/*   Updated: 2024/01/28 23:05:57 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory_part/minitalk.h"
#include "bonus_part/minitalk_bonus.h"

void	mini_putchar(unsigned char c)
{
	write (1, &c, 1);
}

int	mini_atoi(char *str)
{
	int	sign;
	int	i;
	int	result;

	sign = 1;
	result = 0;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while ((str[i]) && (str[i] >= '0' && str[i] <= '9'))
		result = (result * 10) + (str[i++] - '0');
	return (result * sign);
}

void	mini_putnbr(long n)
{
	if (n / 10)
		mini_putnbr((n / 10));
	mini_putchar((n % 10) + 48);
}

void	get_the_pid(void)
{
	pid_t	pid;

	pid = getpid();
	write (1, "\n\
				███╗   ███╗ ██╗███╗   ██╗ ██╗███████╗██╗  ██╗██╗     ██╗  ██╗\n\
				████╗ ████║███║████╗  ██║███║╚════██║██║  ██║██║     ██║ ██╔╝\n\
				██╔████╔██║╚██║██╔██╗ ██║╚██║    ██╔╝███████║██║     █████╔╝ \n\
				██║╚██╔╝██║ ██║██║╚██╗██║ ██║   ██╔╝ ╚════██║██║     ██╔═██╗ \n\
				██║ ╚═╝ ██║ ██║██║ ╚████║ ██║   ██║       ██║███████╗██║  ██╗\n\
				╚═╝     ╚═╝ ╚═╝╚═╝  ╚═══╝ ╚═╝   ╚═╝       ╚═╝╚══════╝╚═╝  ╚═╝\n\
																			\n\
", 971);
	write(1, "\t\t\t\t\t\t\tSERVER PID : ", 20);
	mini_putnbr(pid);
	mini_putchar('\n');
	write(1, "\t\t\t\t\t\t\t   By : oelharbi\n\n", 25);
}
