/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:07:49 by oelharbi          #+#    #+#             */
/*   Updated: 2024/01/29 13:32:08 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	the_handler(int signum, siginfo_t *info, void *useless)
{
	static unsigned char	the_char = 0;
	static int				count_bits = 0;
	static pid_t			client_pid = 0;

	(void)useless;
	if (client_pid != info->si_pid)
	{
		the_char = 0;
		count_bits = 0;
	}
	client_pid = info->si_pid;
	if (signum == SIGUSR1)
		the_char = (the_char << 1) | 1;
	else if (signum == SIGUSR2)
		the_char = the_char << 1;
	count_bits++;
	if (count_bits == 8)
	{
		write(1, &the_char, 1);
		count_bits = 0;
		the_char = 0;
	}
	kill(client_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sa;

	get_the_pid();
	sa.sa_sigaction = &the_handler;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		write(2, "SIGUSR1 FAIL", 12);
		exit (1);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		write(2, "SIGUSR2 FAIL", 12);
		exit (1);
	}
	while (1)
		usleep (50);
	return (0);
}
