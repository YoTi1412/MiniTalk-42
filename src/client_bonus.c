/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrafai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 00:34:37 by yrafai            #+#    #+#             */
/*   Updated: 2024/12/18 00:34:39 by yrafai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

static void	print_message_received(int signal)
{
	if (signal == SIGUSR1)
		ft_printf("✅ Server received message ✅\n");
	exit(0);
}

static int	send_char_bit_by_bit(int pid, char character)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((character & (1 << bit)) != 0)
		{
			if (kill(pid, SIGUSR1) == -1)
			{
				ft_printf("❌ The PID is incorrect ❌\n");
				exit(0);
			}
		}
		else if (kill(pid, SIGUSR2) == -1)
		{
			ft_printf("❌ The PID is incorrect ❌\n");
			exit(0);
		}
		usleep(100);
		bit++;
	}
	return (1);
}

static void	transmit_string(int pid, char input[])
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (!send_char_bit_by_bit(pid, (unsigned char)input[i]))
		{
			ft_printf("❌ Error: Failed to send message ❌\n");
			exit(1);
		}
		i++;
		usleep(100);
	}
	send_char_bit_by_bit(pid, '\0');
}

static int	check_pid(char *str_pid)
{
	int	i;
	int	pid;

	i = 0;
	while (str_pid[i])
	{
		if (!ft_isdigit(str_pid[i]))
		{
			ft_printf("❌ Error: PID must contain only digits ❌\n");
			return (-1);
		}
		i++;
	}
	pid = ft_atoi(str_pid);
	if (pid <= 0)
	{
		ft_printf("❌ Error: Invalid PID ❌\n");
		return (-1);
	}
	return (pid);
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
	{
		ft_printf("⚠️ Usage: %s [PID] [MESSAGE]\n", argv[0]);
		return (1);
	}
	pid = check_pid(argv[1]);
	if (pid == -1)
		return (1);
	signal(SIGUSR1, print_message_received);
	transmit_string(pid, argv[2]);
	while (1)
		pause();
	return (0);
}
