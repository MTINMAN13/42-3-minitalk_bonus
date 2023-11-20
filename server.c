#include "minitalk.h"

volatile sig_atomic_t	g_bit_count = 0;

// instead add sigemptyset if bitcount is (8)
// otherwise do sigaddset 1 or 0

// INSYEAD ONLY ONE GLOBAL VARIABLE/


void	handshake(siginfo_t *info, int starter)
{
	static int	counter;

	counter = 0;
	while (starter == 1)
	{
			++counter;
		if (counter == 1000000000)
		{
			ft_printf("\nReceived from PID %d\n", info->si_pid);
			kill(info->si_pid, SIGUSR2);
			starter = 0;
		}
	}
}

void	handler(int signal, siginfo_t *info, void *context)
{
	int								decoded;
	static volatile char			g_bit_buffer[7];


	(void)info;
	(void)context;
	if (signal == SIGUSR1)
		g_bit_buffer[g_bit_count] = '0';
	else if (signal == SIGUSR2)
		g_bit_buffer[g_bit_count] = '1';
	g_bit_count++;
	if (g_bit_count == 8)
	{
		decoded = ft_atoi_base((char *)g_bit_buffer, "01");
		ft_strlcpy((char *)g_bit_buffer, "00000000", sizeof(g_bit_buffer));
		ft_printf("%c", decoded);
		g_bit_count = 0;
	}
	// handshake(info, 1);
}

// 1. i want to take all the octets, pass them to ascii
// 2. i want to print this shit

// 3. I want to bulk up the code to handle the PID of sending client, to retrieve it and then send a text back to client.

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handler; // Use sa_sigaction instead of sa_handler
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_printf("Error setting up SIGUSR1 handler");
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_printf("Error setting up SIGUSR2 handler");
		exit(EXIT_FAILURE);
	}
	ft_printf("SERVER || %i || ONLINE\n\n", getpid());
	while (1)
		pause();
	return 0;
}

/*

so i in this case want my server to continously run and correctly print out the signal
when its received with the proper PID attached to it. I do have a separate client program
already made. I also want the server to exit when i send "exit" into it


*/