/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:38:01 by oelharbi          #+#    #+#             */
/*   Updated: 2024/01/28 23:17:04 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int	g_stop_conflict = 0;

void	send_acknowledgement(int signum)
{
	if (signum == SIGUSR1)
		write(1, "SEND HAS BEEN DONE SUCCESSFULLY!\n", 33);
	if (signum == SIGUSR2)
		g_stop_conflict = 1;
}

void	send_bits(int pid, int bit)
{
	int	signal;

	signal = 0;
	if (bit == 1)
		signal = SIGUSR1;
	else if (bit == 0)
		signal = SIGUSR2;
	if (kill(pid, signal) == -1)
	{
		write (2, "CHECK THE PID PLEASE!!\n", 23);
		exit(1);
	}
	while (!g_stop_conflict)
		continue ;
	g_stop_conflict = 0;
}

void	char_handling(int pid, unsigned char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		send_bits(pid, (c >> i) & 1);
		usleep(300);
		i--;
	}
}

void	string_handling(int pid, const char *message)
{
	int	i;

	i = 0;
	while (message[i])
		char_handling(pid, message[i++]);
	char_handling(pid, '\0');
}

int	main(int argc, char *argv[])
{
	pid_t	pid;

	if (argc != 3)
	{
		write (2, "INVALID ARGUMENT!\n", 18);
		write (2, "USE IT LIKE THIS : ./client [PID] [STRING]\n", 43);
		exit(1);
	}
	pid = mini_atoi(argv[1]);
	if (pid <= 0)
	{
		write(2, "PLEASE ENTER A VALID PID!!", 26);
		exit(1);
	}
	signal(SIGUSR1, send_acknowledgement);
	signal(SIGUSR2, send_acknowledgement);
	string_handling(pid, argv[2]);
	return (0);
}
