# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 17:03:14 by oelharbi          #+#    #+#              #
#    Updated: 2024/01/28 22:34:13 by oelharbi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

COBJ = mandatory_part/client.c utils.c
SOBJ = mandatory_part/server.c utils.c

BONUS_COBJ = bonus_part/client_bonus.c utils.c
BONUS_SOBJ = bonus_part/server_bonus.c utils.c

all: client server

bonus: client_bonus server_bonus

client_bonus: $(BONUS_COBJ) bonus_part/minitalk_bonus.h
	$(CC) $(CFLAGS) $(BONUS_COBJ) -o client_bonus

server_bonus: $(BONUS_SOBJ) bonus_part/minitalk_bonus.h
	$(CC) $(CFLAGS) $(BONUS_SOBJ) -o server_bonus

client: $(COBJ) mandatory_part/minitalk.h
	$(CC) $(CFLAGS) $(COBJ) -o client

server: $(SOBJ) mandatory_part/minitalk.h
	$(CC) $(CFLAGS) $(SOBJ) -o server

clean: 
	rm -f client server client_bonus server_bonus

fclean: clean

re: fclean all bonus

.PHONY: clean
