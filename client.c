/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 21:24:18 by mman              #+#    #+#             */
/*   Updated: 2023/11/20 21:24:23 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// SO TO IMPLEMENT THE BONUS< I WILL FIRST TRACK THE LENGTH OF THE TRANSMISSION AND SEND IT AT THE BEGINNING OF THIS TRANSMISSION
// THEN AFTER THE TRANSMISSION IS RECEIVED IN FULL< I WILL SEND BACK THE HANDSHAKE

#include "minitalk.h"

int	county(char	*input)
{
	unsigned char	bit;
	unsigned char	octet;
	int				i;
	int				j;
	size_t			trans_length;

	if (!input)
		return (0);
	trans_length = 0;
	j = 0;
	while (input[j])
	{
		octet = input[j];
		i = 7;
		while (i >= 0)
		{
			bit = (octet >> i) & 1;
			i--;
		}
		j++;
	}
	return (trans_length);
}

void	send_signal(int pid,char *msg)
{
	int				i; // Start from the most significant bit
	unsigned char	bit;
	unsigned char 	octet;
	int				len;

	i = 7;
	octet = 0;
	len = county(msg);
	while (msg[i])
	{
		bit = (unsigned char)msg[i];
		while (i >= 0)
		{
			bit = (octet >> i) & 1; // Extract the i-th bit
			if (bit == 0)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			// usleep(100);
			i--;
		}
	ft_printf("\n");
	i++;
	}
}

void	ft_error(int num, char *thing) {
	if (num <= 2)
		ft_printf("ERROR | You sent an insufficient number of parameters.\n");
	else if (num >= 4)
		ft_printf("ERROR | Too many parameters!\n");
	if (!(thing[0] > 47 && thing[0] < 58))
		ft_printf("\n\nERROR | The provided PID parameter is not an integer. Pls... \n");
}

void	receiver()
{

}

int	main(int argc, char **argv)
{
	int		pid;
	char	*str_send;
	int		i;

	if (argc != 3 || !(argv[1][0] > 47 && argv[1][0] < 58))
	{
		ft_error(argc, argv[1]);
		return (-1);
	}
	pid = ft_atoi(argv[1]);
	str_send = argv[2];
	i = 0;
	while (str_send[i])
	{
		send_signal(pid, str_send);
		i++;
	}
	ft_printf("CLIENT | Sending %d symbols:\nCLIENT | %s", i, argv[2]);
	return (0);
}

// after sending the signal, pause up until we receive the signal back.
// if we dont receive it after a brief pause, say no such servers
