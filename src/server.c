/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrafai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 00:34:51 by yrafai            #+#    #+#             */
/*   Updated: 2024/12/18 00:34:52 by yrafai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

static void	process_char(char c, int pid)
{
	if (c == '\0')
	{
		ft_printf("\n✅ Message received from PID %d ✅\n", pid);
		kill(pid, SIGUSR1);
	}
	else
		ft_printf("%c", c);
}

static void	handle_signal(int signal, siginfo_t *info, void *context)
{
	static char	c;
	static int	bit;
	static int	pid;

	(void)context;
	if (!pid)
		pid = info->si_pid;
	if (pid != info->si_pid)
	{
		pid = info->si_pid;
		c = 0;
		bit = 0;
	}
	if (signal == SIGUSR1)
		c |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		process_char(c, pid);
		c = 0;
		bit = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;
	int					pid;

	pid = getpid();
	ft_printf("👉 Server PID: %d 👈\n", pid);
	ft_printf("⏳ Waiting for messages... ⏳\n");
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
