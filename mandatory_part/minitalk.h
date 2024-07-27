/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:39:36 by oelharbi          #+#    #+#             */
/*   Updated: 2024/01/28 22:31:48 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H  

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>

void	mini_putchar(unsigned char c);
int		mini_atoi(char *str);
void	mini_putnbr(long n);
void	get_the_pid(void);

#endif
