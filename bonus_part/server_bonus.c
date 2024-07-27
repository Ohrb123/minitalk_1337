/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:07:49 by oelharbi          #+#    #+#             */
/*   Updated: 2024/01/28 23:06:29 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int	check_bytes(unsigned char c)
{
	if (c >= 240)
		return (4);
	else if (c >= 224 && c < 240)
		return (3);
	else if (c >= 192 && c < 224)
		return (2);
	else
		return (1);
}

void	print_bytes(unsigned char c, pid_t pid)
{
	static int				i;
	static int				j;
	static unsigned char	arr[4];
	static pid_t			old_pid;
	int						index;

	if (old_pid != pid)
	{
		i = 0;
		j = 0;
		old_pid = pid;
	}
	if (i == 0)
		i = check_bytes(c);
	arr[j] = c;
	j++;
	if (j == i)
	{
		index = 0;
		while (index < j)
			write(1, &arr[index++], 1);
		i = 0;
		j = 0;
	}
}

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
		if (the_char == '\0')
			kill(client_pid, SIGUSR1);
		print_bytes(the_char, client_pid);
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
		pause();
	return (0);
}
